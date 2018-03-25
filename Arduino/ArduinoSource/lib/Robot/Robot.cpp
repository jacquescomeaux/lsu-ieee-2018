#include <Robot.h>

Robot::Robot() :
  motor_shields {
    MotorShield(0x61),
    MotorShield(0x62)
  },
  stopped(true),
  flags(Flag::NONE),
  NUM_TASKS(6),
  last_ran {0},
  XP(Fixed(0.02)),
  YP(Fixed(0.02)),
  RotP(Fixed(0.02)),
  base_speed(Fixed(90)),
  veer_amount(Fixed(10)),
  acceleration(Fixed(10)),
  current_direction(Direction::NONE),
  wheels {
    //Interrupt Pins: 2, 3, 18, 19, 20, 21
    Wheel(motor_shields[0].getMotor(1),  2,  4), //FRONT_LEFT
    Wheel(motor_shields[0].getMotor(2),  3,  5), //BACK_LEFT
    Wheel(motor_shields[1].getMotor(1), 18, 8), //BACK_RIGHT
    Wheel(motor_shields[1].getMotor(2), 19, 9)  //FRONT_RIGHT
  },
  edge_detectors {
    ProximitySensor(6, 7),   //FRONT(0)
    ProximitySensor(8, 9),   //LEFT(1)
    ProximitySensor(10, 11), //BACK(2)
    ProximitySensor(12, 14)  //RIGHT(3)
  },
  line_sensor() {
    stop();
    pinMode(A8, INPUT);
    pinMode(A9, INPUT);
}

void Robot::checkEdges() {
  for(ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();
}

void Robot::setWheelSpeeds(const Fixed* speeds) {
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
  veer(XP*xerr, YP*yerr, RotP*roterr);
}

void Robot::stop() {
  flags &= ~Flag::FOLLOWING_LINE;
  flags &= ~Flag::CENTERING_CROSS;
  flags &= ~Flag::CENTERING_CORNER;
  for(Wheel& w : wheels) w.stop();
}

bool Robot::ready() {
  int go = digitalRead(A8);
  int stop = digitalRead(A9);
  if(go == HIGH) stopped = false;
  if(stop == HIGH) stopped = true;
  return stopped;
}

void Robot::update() {
  int dt[NUM_TASKS];
  int time = millis();
  for(int i = 0; i < NUM_TASKS; i++)  dt[i] = time - last_ran[i];
  
  if((dt[0] > 100) ? (last_ran[0] = time) : false) {
    for(Wheel& w : wheels) w.approachSpeed(acceleration);
  }

  if((dt[1] > 0) ? (last_ran[1] = time) : false) {
    if((flags & Flag::FOLLOWING_LINE) != Flag::NONE) correctErrors();
  }
  
  if((dt[2] > 10) ? (last_ran[2] = time) : false) {
    if((flags & Flag::CALIBRATING_LINE) != Flag::NONE) line_sensor.calibrateSensors();
  }
  
  if((dt[3] > 1000) ? (last_ran[3] = time) : false) {
    if((flags & Flag::PRINTING_LINE) != Flag::NONE) line_sensor.printReadings(); 
  }
  
  if((dt[4] > 100) ? (last_ran[4] = time) : false) {
    //checkEdges();
  }
  
  if((dt[5] > 100) ? (last_ran[5] = time) : false) {
    if((flags & Flag::TRAVEL_TO_DST) != Flag::NONE) checkDestination();
  }
}

void Robot::center(int offset) {
  stop();
  Fixed xerr, yerr, roterr;
  line_sensor.getLineErrors(&xerr, &yerr, &roterr, offset);
  veer(XP*xerr, YP*yerr, RotP*roterr);
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
    case(Direction::CLOCKWISE): move(ZERO, ZERO, ZERO - speed); break;
    case(Direction::COUNTER_CLOCKWISE): move(ZERO, ZERO, speed); break;
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
  if(dir == BACK) {
	stepsToTravel = 0 - stepsToTravel; //set steps negative
  }
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
  Flag diff = flags ^ settings;
  if((flags & diff & Flag::CALIBRATING_LINE) != Flag::NONE) Serial.println("CALIBRATING_LINE set");  
  if((~flags & diff & Flag::CALIBRATING_LINE) != Flag::NONE) Serial.println("CALIBRATING_LINE set");  
  if((flags & diff & Flag::FOLLOWING_LINE) != Flag::NONE) Serial.println("FOLLOWING_LINE set"); 
  if((~flags & diff & Flag::FOLLOWING_LINE) != Flag::NONE) Serial.println("FOLLOWING_LINE set"); 
  if((flags & diff & Flag::PRINTING_LINE) != Flag::NONE) Serial.println("PRINTING_LINE set"); 
  if((~flags & diff & Flag::PRINTING_LINE) != Flag::NONE) Serial.println("PRINTING_LINE set"); 
}

void Robot::adjustXP(Fixed adjustment) {
  XP += adjustment;
  Serial.print("XP = ");
  Serial.println(XP.getDouble());
}

void Robot::adjustYP(Fixed adjustment) {
  YP += adjustment;
  Serial.print("YP = ");
  Serial.println(YP.getDouble());
}

void Robot::adjustRotP(Fixed adjustment) {
  RotP += adjustment;
  Serial.print("RotP = ");
  Serial.println(RotP.getDouble());
}

void Robot::adjustBaseSpeed(Fixed adjustment) {
  base_speed += adjustment;
  Serial.print("Speed = ");
  Serial.println(base_speed.getInt());
}

SortBot::SortBot() {}//SortingSystem(Robot::motor_shields[0].getStepper(200, 3), Robot::motor_shields[0].getStepper(200, 3)) {}
  //needs real pin numbers
