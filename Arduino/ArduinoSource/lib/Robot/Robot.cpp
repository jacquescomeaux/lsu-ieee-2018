#include <Robot.h>

Robot::Robot() :
  motor_shields {
    MotorShield(0x61),
    MotorShield(0x62)
  },
  flags(Flag::NONE),
  NUM_TASKS(6),
  last_ran {0},
  XP(Fixed(2.3)),
  YP(Fixed(2.3)),
  RotP(Fixed(2.03)),
  base_speed(Fixed(90)),
  veer_amount(Fixed(10)),
  acceleration(Fixed(10)),
  current_direction(Direction::NONE),
  wheels {
    //Interrupt Pins: 2, 3, 18, 19, 20, 21
    Wheel(motor_shields[0].getMotor(1),  2,  4),
    Wheel(motor_shields[0].getMotor(2),  3,  5),
    Wheel(motor_shields[1].getMotor(1), 18, 22),
    Wheel(motor_shields[1].getMotor(2), 19, 23)
  },
  /*edge_detectors {
    ProximitySensor(5, 6),
    ProximitySensor(0, 0),
    ProximitySensor(0, 0),
    ProximitySensor(0, 0)
  },*/
  line_sensor() {
    stop();
} 

void Robot::checkEdges() {
  //for(const ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();
  //if(edge_detectors[0].edgeDetected()) stop();
  //Serial.println(edge_detectors[0].getProximity());
}

void Robot::setWheelSpeeds(const Fixed* speeds) {
  //for(int i = 0; i < 4; i++) Serial.println(speeds[i].getInt());
  for(int i = 0; i < 4; i++) wheels[i].setSpeed(speeds[i]);
}

void Robot::adjustWheelSpeeds(const Fixed* speeds) {
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed(speeds[i]);
}

void Robot::correctWheelSpeeds(const Fixed* speeds) {
  for(int i = 0; i < 4; i++) wheels[i].correctSpeed(speeds[i]);
}

void Robot::correctErrors() {
  Fixed xerr, yerr, roterr;
  line_sensor.getLineErrors(&xerr, &yerr, &roterr, current_direction);
 /* Serial.println(xerr.getDouble());
  Serial.println(yerr.getDouble());
  Serial.println(roterr.getDouble());
  Serial.println(" ");
  */veer(XP*xerr, YP*yerr, RotP*roterr);
}

void Robot::stop() {
  for(Wheel& w : wheels) w.stop();
}

void Robot::update() {
  int dt[NUM_TASKS];
  int time = millis();
  for(int i = 0; i < NUM_TASKS; i++)  dt[i] = time - last_ran[i];
  
  if((dt[0] > 100) ? (last_ran[0] = time) : false) {
    for(Wheel& w : wheels) w.approachSpeed(acceleration);
  }

  if((dt[1] > 100) ? (last_ran[1] = time) : false) {
    if((flags & Flag::FOLLOWING_LINE) != Flag::NONE) correctErrors();
  }
  
  if((dt[2] > 100) ? (last_ran[2] = time) : false) {
    if((flags & Flag::CALIBRATING_LINE) != Flag::NONE) line_sensor.calibrateSensors();
  }
  
  if((dt[3] > 1000) ? (last_ran[3] = time) : false) {
    if((flags & Flag::PRINTING_LINE) != Flag::NONE) ;//line_sensors[static_cast<int>(current_direction)].printReadings(); 
  }
  
  if((dt[4] > 100) ? (last_ran[4] = time) : false) {
    checkEdges();
  }
  
  if((dt[5] > 100) ? (last_ran[5] = time) : false) {
    if((flags & Flag::TRAVEL_TO_DST) != Flag::NONE) checkDestination();
  }
}

void Robot::move(Direction dir) {
  move(dir, base_speed);
}

void Robot::move(Direction dir, Fixed speed) {
  current_direction = dir;
  switch(dir) {
    case(Direction::NONE): stop(); break;
    case(Direction::FRONT): move(ZERO, speed, ZERO); break;
    case(Direction::BACK): move(ZERO, ZERO - speed, ZERO); break;
    case(Direction::LEFT): move(ZERO - speed, ZERO, ZERO); break;
    case(Direction::RIGHT): move(speed, ZERO, ZERO); break;
    case(Direction::FRONT_LEFT): move(ZERO - speed * SQRT_HALF, speed * SQRT_HALF, ZERO); break;
    case(Direction::FRONT_RIGHT): move(speed * SQRT_HALF, speed * SQRT_HALF, ZERO); break;
    case(Direction::BACK_LEFT): move(ZERO - speed * SQRT_HALF, ZERO - speed * SQRT_HALF, ZERO); break;
    case(Direction::BACK_RIGHT): move(speed * SQRT_HALF, ZERO - speed * SQRT_HALF, ZERO); break;
    case(Direction::CLOCKWISE): move(ZERO, ZERO, speed); break;
    case(Direction::COUNTER_CLOCKWISE): move(ZERO, ZERO, ZERO - speed); break;
    default: break; 
  }
}

void Robot::move(Fixed x, Fixed y, Fixed rot) {
  const Fixed speeds[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  setWheelSpeeds(speeds);
}

void Robot::travel(Direction dir, Fixed dist) {
  travel(dir, base_speed, dist);
}

void Robot::travel(Direction dir, Fixed speed, Fixed distance) {
  Fixed stepsToTravel = distance * 287; //286.7 steps per inch
  for(int i = 0; i < 4; i++) {
    current_wheel_pos[i] = wheels[i].getPosition();
    target_wheel_pos[i] = current_wheel_pos[i] + stepsToTravel;
  }
  flags |= Flag::TRAVEL_TO_DST; //enable flag
  Serial.println("Setting Flag TRAVEL_TO_DST");
  move(dir, speed);
}

void Robot::checkDestination() {
  for(int i = 0; i < 4; i++) {
    current_wheel_pos[i] = wheels[i].getPosition();
    Fixed speed = wheels[i].getSpeed();
    bool forward; //check if wheel is moving in positive/negative direction
    if(speed > 0) {
      forward = true;
    }
    else {
      forward = false;
    }
    
    //Debug Serial Printing
    Serial.print("Wheel ");
    Serial.print(i);
    Serial.print(" has ");
    Serial.print((target_wheel_pos[i] - current_wheel_pos[i]).getInt());
    Serial.println(" steps remaining.");

    Serial.print("current_wheel_pos: ");
    Serial.println(current_wheel_pos[i].getInt());
    Serial.print("target_wheel_pos: ");
    Serial.println(target_wheel_pos[i].getInt());
    Serial.print("abs(target_wheel_pos[i]): ");
    Serial.println(abs(target_wheel_pos[i].getInt()));

    if(forward == true) {
      if (current_wheel_pos[i] >= target_wheel_pos[i]) {
        flags &= ~Flag::TRAVEL_TO_DST; //end moveSetDistance
	stop(); //stop all wheels once 1 wheel has gone desired distance
      }
    }
    else if (current_wheel_pos[i] <= target_wheel_pos[i]) {
      flags &= ~Flag::TRAVEL_TO_DST;
      stop();
    }
  }
}

void Robot::veer(Direction dir) {
  veer(dir, veer_amount);
}

void Robot::veer(Direction dir, Fixed amount) {
  switch(dir) {
    case(Direction::NONE): break;
    case(Direction::BACK): veer(ZERO, ZERO - amount, ZERO); break;
    case(Direction::LEFT): veer(ZERO - amount, ZERO, ZERO); break;
    case(Direction::RIGHT): veer(amount, ZERO, ZERO); break;
    case(Direction::FRONT_LEFT): veer(ZERO - amount * SQRT_HALF, amount * SQRT_HALF, ZERO); break;
    case(Direction::FRONT_RIGHT): veer(amount * SQRT_HALF, amount * SQRT_HALF, ZERO); break;
    case(Direction::BACK_LEFT): veer(ZERO - amount * SQRT_HALF, ZERO - amount * SQRT_HALF, ZERO); break;
    case(Direction::BACK_RIGHT): veer(amount * SQRT_HALF, ZERO - amount * SQRT_HALF, ZERO); break;
    case(Direction::CLOCKWISE): veer(ZERO, ZERO, amount); break;
    case(Direction::COUNTER_CLOCKWISE): veer(ZERO, ZERO, ZERO - amount); break;
    default: break; 
  }
}

void Robot::veer(Fixed x, Fixed y, Fixed rot) {
  const Fixed adjustments[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  correctWheelSpeeds(adjustments);
  //adjustWheelSpeeds(adjustments);
}

void Robot::toggle(Flag settings) {
  settings &= ~Flag::NONE;
  flags ^= settings;
  if((flags & Flag::CALIBRATING_LINE) != Flag::NONE) Serial.println("CalibratingLine"); 
  if((flags & Flag::FOLLOWING_LINE) != Flag::NONE) Serial.println("FollowingLine"); 
}

void Robot::adjustXP(Fixed adjustment) {
  XP += adjustment;
  Serial.print("XP = ");
  Serial.println(XP.getDouble());
}

void Robot::adjustYP(Fixed adjustment) {
  YP += adjustment;
  Serial.print("YP = ");
  Serial.println(YP.getInt());
}

void Robot::adjustRotP(Fixed adjustment) {
  RotP += adjustment;
  Serial.print("RotP = ");
  Serial.println(RotP.getInt());
}

void Robot::adjustBaseSpeed(Fixed adjustment) {
  base_speed += adjustment;
  Serial.print("Speed = ");
  Serial.println(base_speed.getInt());
}

SortBot::SortBot() :
  //motor_shields {
 //   MotorShield(0x61),
   // MotorShield(0x62)
 // },
  //needs real pin numbers
  SortingSystem(Robot::motor_shields[0].getStepper(200, 1), Robot::motor_shields[0].getStepper(200, 2)) {}
