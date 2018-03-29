#include <Robot.h>

Robot::Robot() :
  motor_shields {
    MotorShield(0x61), //wheels
    MotorShield(0x62), //1:Token Arm 2:Sorting Plate
    MotorShield(0x60)  //magnet
  },
  stopped(true),
  flags(Flag::NONE),
  pid_terms {
    //Proportional //Integral    //Derivitave  //Accum.  //Last error
    /*{Fixed(0.000), Fixed(0.000), Fixed(0.000), Fixed(0), Fixed(0)}, //x terms  //P: 0.014 D: 0.0600
    {Fixed(0.000), Fixed(0.000), Fixed(0.000), Fixed(0), Fixed(0)}, //y terms  //P: 0.005 D: 0.0500
    {Fixed(0.000), Fixed(0.000), Fixed(0.000), Fixed(0), Fixed(0)}, //rot terms //best so far: P: 0.037 D: 0.1
   */
    {Fixed(0.060), Fixed(0.010), Fixed(0.300), Fixed(0), Fixed(0)}, //x terms  //P: 0.014 D: 0.0600
    {Fixed(0.060), Fixed(0.002), Fixed(0.100), Fixed(0), Fixed(0)}, //y terms  //P: 0.005 D: 0.0500
    {Fixed(0.020), Fixed(0.0005), Fixed(0.070), Fixed(0), Fixed(0)}, //rot terms //best so far: P: 0.037 D: 0.1
    ///{Fixed(0.012), Fixed(0.0004), Fixed(0.060), Fixed(0), Fixed(0)}, //x terms  //P: 0.014 D: 0.0600
    //{Fixed(0.005), Fixed(0.0004), Fixed(0.050), Fixed(0), Fixed(0)}, //y terms  //P: 0.005 D: 0.0500
    //{Fixed(0.037), Fixed(0.0004), Fixed(0.100), Fixed(0), Fixed(0)}, //rot terms //best so far: P: 0.037 D: 0.1
  },
  base_speed(Fixed(90)),
  veer_amount(Fixed(10)),
  acceleration(Fixed(20)), //previously set at 10
  current_direction(Direction::NONE),
  wheels {
    //Interrupt Pins: 2, 3, 18, 19, 20, 21
    Wheel(motor_shields[0].getMotor(1),  2, 4), //FRONT_LEFT
    Wheel(motor_shields[0].getMotor(2),  3, 5), //BACK_LEFT
    Wheel(motor_shields[0].getMotor(3), 18, 16), //BACK_RIGHT
    Wheel(motor_shields[0].getMotor(4), 19, 17)  //FRONT_RIGHT
  },
  edge_detectors {
    ProximitySensor( 6,  7), //RIGHT(0)
    ProximitySensor( 8,  9), //FRONT(1)
    ProximitySensor(10, 11), //LEFT(2)
    //ProximitySensor(12, 14)  //BACK(3)
  },
  line_sensor(),
  debug(false) {  //if we wrap our Serial.prints checking for this we can toggle it more easily than commenting.
    stop();
    pinMode(A8, INPUT);
    pinMode(A9, INPUT);
}

void Robot::resolveDirection(Direction dir, Fixed* x, Fixed* y, Fixed* rot) {
  static const Fixed ZERO = 0, POS_ONE = 1, NEG_ONE = -1, POS_SQRT_HALF = sqrt(0.5), NEG_SQRT_HALF = -1 * sqrt(0.5);
  auto assign = [&] (Fixed x_new, Fixed y_new, Fixed rot_new) {*x = x_new; *y = y_new; *rot = rot_new;};
  switch(dir) {
    case(Direction::NONE): assign(ZERO, ZERO, ZERO); break;
    case(Direction::FRONT): assign(ZERO, POS_ONE, ZERO); break;
    case(Direction::BACK):  assign(ZERO, NEG_ONE, ZERO); break;
    case(Direction::LEFT):  assign(NEG_ONE, ZERO, ZERO); break;
    case(Direction::RIGHT): assign(POS_ONE, ZERO, ZERO); break;
    case(Direction::FRONT_LEFT):  assign(NEG_SQRT_HALF, POS_SQRT_HALF, ZERO); break;
    case(Direction::FRONT_RIGHT): assign(POS_SQRT_HALF, POS_SQRT_HALF, ZERO); break;
    case(Direction::BACK_LEFT):   assign(NEG_SQRT_HALF, NEG_SQRT_HALF, ZERO); break;
    case(Direction::BACK_RIGHT):  assign(POS_SQRT_HALF, NEG_SQRT_HALF, ZERO); break;
    case(Direction::CLOCKWISE):         assign(ZERO, ZERO, NEG_ONE); break;
    case(Direction::COUNTER_CLOCKWISE): assign(ZERO, ZERO, POS_ONE); break;
    default: break;
  }
}

void Robot::checkEdges() {
  //for(ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();

  //DEBUGGING CODE
  for (int s = 0; s < 3; s++) {
	Serial.print("S: ");
	Serial.print(s);
	Serial.print("  ");
	if (edge_detectors[s].edgeDetected()) {}
	Serial.print(" | ");
  }
  Serial.println(" | ");

  /* COMMENTED OUT WORKING CODE
  if(current_direction == Direction::FRONT) if(edge_detectors[1].edgeDetected()) stop();
  //if(current_direction == Direction::BACK) if(edge_detectors[3].edgeDetected()) stop();
  if(current_direction == Direction::LEFT) if(edge_detectors[2].edgeDetected()) stop();
  if(current_direction == Direction::RIGHT) if(edge_detectors[0].edgeDetected()) stop();
  */
}

void Robot::checkDestination() {
  for(int i = 0; i < 2; i++) {
    if((wheels[i].getSpeed() > Fixed(0)) != (wheels[i].getPosition() >= target_wheel_pos[i])) continue;
    flags &= ~Flag::TRAVEL_TO_DST;
    stop();
  }
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

void Robot::center(bool cross, int offset) {
  Fixed xerr, yerr, rerr;
  if(crosss) line_sensor.getCrossIntersectionErrors(&xerr, &yerr, &rerr, offset);
  else line_sensor.getCornerIntersectionErrors(&xerr, &yerr, &rerr, offset);
  correctErrors(xerr, yerr, rerr);
}

void Robot::correctErrors(Fixed xerr, Fixed yerr, Fixed rerr, int dir) {
  if(((flags & Flag::CENTERING_CORNER) != Flag::NONE) || ((flags & Flag::CENTERING_CROSS) != Flag::NONE)) for(int i = 0; i < 3; i++) pid_terms[i][3] = Fixed(0);
  static bool filled = false;
  static const Fixed FIFTH = 0.2;
  static unsigned long t = 0;
  static Fixed prev_errors[3][5] = {0};
  prev_errors[0][t] = xerr;
  prev_errors[1][t] = yerr;
  prev_errors[2][t] = rerr;
  Fixed avgs[3];
  for(int i = 0; i < 3; i++) {
    for(Fixed f : prev_errors[i]) avgs[i] += f;
    avgs[i] *= FIFTH;
  }
  if(filled) veer(
    //PID CONTROLLER
    //KP * current error        +  KI * accumulated error             +  KD * change in error
    (pid_terms[0][0]  * avgs[0]) + (pid_terms[0][1] * pid_terms[0][3]) + (pid_terms[0][2] * (avgs[0] - pid_terms[0][4])), //x correction
    (pid_terms[1][0]  * avgs[1]) + (pid_terms[1][1] * pid_terms[1][3]) + (pid_terms[1][2] * (avgs[1] - pid_terms[1][4])), //y correction
    (pid_terms[2][0]  * avgs[2]) + (pid_terms[2][1] * pid_terms[2][3]) + (pid_terms[2][2] * (avgs[2] - pid_terms[2][4]))  //rot correction
  );
  pid_terms[0][3] += xerr;
  pid_terms[1][3] += yerr;
  pid_terms[2][3] += rerr;
  pid_terms[0][4]  = avgs[0];
  pid_terms[1][4]  = avgs[1];
  pid_terms[2][4]  = avgs[2];
  if(debug) {
    Serial.print("Time");
    Serial.println(millis());
    reportWheelSpeeds();
  }
  if(t == 4) filled = true;
  if(++t >= 5) t = 0;
}

void Robot::stop() {
  flags &= ~Flag::FOLLOWING_LINE;
  flags &= ~Flag::CENTERING_CROSS;
  flags &= ~Flag::CENTERING_CORNER;
  for(Wheel& w : wheels) w.stop();
  for(int i = 0; i < 3; i++) pid_terms[i][3] = Fixed(0);
}

bool Robot::ready() {
  int go = digitalRead(A8);
  int stop = digitalRead(A9);
  if(go == HIGH) stopped = false;
  if(stop == HIGH) stopped = true;
  return !stopped;
}

void Robot::update() {
  static const int NUM_TASKS = 8;
  static unsigned long last_ran[NUM_TASKS] = {0};
  unsigned long dt[NUM_TASKS];
  unsigned long time = millis();
  for(int i = 0; i < NUM_TASKS; i++)  dt[i] = time - last_ran[i];
  
  if((dt[0] > 100) ? (last_ran[0] = time) : false) {
    for(Wheel& w : wheels) w.approachSpeed(acceleration);
  }

  if((dt[1] > 0) ? (last_ran[1] = time) : false) {
    if((flags & Flag::FOLLOWING_LINE) != Flag::NONE) {
      Fixed xerr, yerr, rerr;
      line_sensors.getLineErrors(&xerr, &yerr, &rerr, current_direction, 2);
      correctErrors();
    }
  }
  
  if((dt[2] > 10) ? (last_ran[2] = time) : false) {
    if((flags & Flag::CALIBRATING_LINE) != Flag::NONE) {
      line_sensor.calibrateSensors();
      line_sensor.printCalibratedValues();
    }
  }
  
  if((dt[3] > 1000) ? (last_ran[3] = time) : false) {
    if((flags & Flag::PRINTING_LINE) != Flag::NONE) line_sensor.printReadings(); 
  }
  
  if((dt[4] > 100) ? (last_ran[4] = time) : false) {
    if((flags & Flag::STOPPING_INT) != Flag::NONE) if(line_sensor.countLinePeaks(1) == 4) stop();
    //checkEdges();
  }
  
  if((dt[5] > 100) ? (last_ran[5] = time) : false) {
    if((flags & Flag::TRAVEL_TO_DST) != Flag::NONE) checkDestination();
  }
  
  if((dt[6] > 0) ? (last_ran[6] = time) : false) {
    if((flags & Flag::CENTERING_CROSS) != Flag::NONE) center(true, 0);
  }
  
  if((dt[7] > 0) ? (last_ran[7] = time) : false) {
    if((flags & Flag::CENTERING_CORNER) != Flag::NONE) center(false, 16);
  }
  
  if(!ready()) stop();
}

void Robot::move(Direction dir) {
  move(dir, base_speed);
}

void Robot::move(Direction dir, Fixed speed) {
  current_direction = dir;
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  move(speed * x, speed * y, speed * rot);
}

void Robot::move(Fixed x, Fixed y, Fixed rot) {
  const Fixed speeds[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  setWheelSpeeds(speeds);
}

void Robot::veer(Direction dir) {
  veer(dir, veer_amount);
}

void Robot::veer(Direction dir, Fixed amount) {
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  veer(amount * x, amount * y, amount * rot);
}

void Robot::veer(Fixed x, Fixed y, Fixed rot) {
  const Fixed adjustments[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  correctWheelSpeeds(adjustments);
}

void Robot::steer(Direction dir) {
  steer(dir, veer_amount);
}

void Robot::steer(Direction dir, Fixed amount) {
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  steer(amount * x, amount * y, amount * rot);
}

void Robot::steer(Fixed x, Fixed y, Fixed rot) {
  const Fixed adjustments[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  adjustWheelSpeeds(adjustments);
}

void Robot::travel(Direction dir, Fixed dist) {
  travel(dir, dist, base_speed);
}

void Robot::travel(Direction dir, Fixed dist, Fixed speed) {
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  travel(speed * x, speed * y, speed * rot, dist);
}

void Robot::travel(Fixed x, Fixed y, Fixed rot, Fixed dist) {
  static const Fixed STEPS_PER_INCH = 286.7, ZERO = 0, POS_ONE = 1, NEG_ONE = -1;
  Fixed steps_to_travel = dist * STEPS_PER_INCH;
  const Fixed speeds[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  for(int i = 0; i < 2; i++) target_wheel_pos[i] = wheels[i].getPosition() + steps_to_travel * ((speeds[i] > ZERO) ? POS_ONE : NEG_ONE);
  flags |= Flag::TRAVEL_TO_DST;
  setWheelSpeeds(speeds);
}

void Robot::toggle(Flag settings) {
  settings &= ~Flag::NONE;
  flags ^= settings;
  if((flags & settings & Flag::CALIBRATING_LINE) != Flag::NONE) Serial.println("CALIBRATING_LINE set");  
  if((~flags & settings & Flag::CALIBRATING_LINE) != Flag::NONE) Serial.println("CALIBRATING_LINE cleared");  
  if((flags & settings & Flag::FOLLOWING_LINE) != Flag::NONE) Serial.println("FOLLOWING_LINE set"); 
  if((~flags & settings & Flag::FOLLOWING_LINE) != Flag::NONE) Serial.println("FOLLOWING_LINE cleared"); 
  if((flags & settings & Flag::PRINTING_LINE) != Flag::NONE) Serial.println("PRINTING_LINE set"); 
  if((~flags & settings & Flag::PRINTING_LINE) != Flag::NONE) Serial.println("PRINTING_LINE cleared"); 
  if((flags & settings & Flag::STOPPING_INT) != Flag::NONE) Serial.println("STOPPING_INT set"); 
  if((~flags & settings & Flag::STOPPING_INT) != Flag::NONE) Serial.println("STOPPING_INT cleared"); 
  if((flags & settings & Flag::CENTERING_CROSS) != Flag::NONE) Serial.println("CENTERING_CROSS set"); 
  if((~flags & settings & Flag::CENTERING_CROSS) != Flag::NONE) Serial.println("CENTERING_CROSS cleared"); 
  if((flags & settings & Flag::CENTERING_CORNER) != Flag::NONE) Serial.println("CENTERING_CORNER set"); 
  if((~flags & settings & Flag::CENTERING_CORNER) != Flag::NONE) Serial.println("CENTERING_CORNER cleared"); 
}

void Robot::adjustPID(unsigned int var, unsigned int term, Fixed adjustment) {
  if(var > 2 || term > 2) return;
  pid_terms[var][term] += adjustment;
  if(var == 0) Serial.print("X");
  if(var == 1) Serial.print("Y");
  if(var == 2) Serial.print("Rot");
  if(term == 0) Serial.print("P = ");
  if(term == 1) Serial.print("I = ");
  if(term == 2) Serial.print("D = ");
  Serial.println(pid_terms[var][term].getDouble(), 4);
}

void Robot::adjustBaseSpeed(Fixed adjustment) {
  base_speed += adjustment;
  Serial.print("Speed = ");
  Serial.println(base_speed.getInt());
}

void Robot::reportWheelSpeeds() {
  for(int i = 0; i < 4; i++) {
    Fixed report = wheels[i].getActualSpeed();
    Serial.print("Wheel ");
    Serial.print(i);
    Serial.print("-->");
    Serial.println(report.getInt());
  }
}

SortBot::SortBot() : SortingSystem(Robot::motor_shields[1].getStepper(200, 1), Robot::motor_shields[2].getMotor(1), Robot::motor_shields[1].getStepper(200, 2)) {}

void SortBot::update() {
  continueSorting();
  Robot::update();
}
