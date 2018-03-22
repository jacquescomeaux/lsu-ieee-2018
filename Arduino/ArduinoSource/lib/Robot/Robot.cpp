#include <Robot.h>

Robot::Robot() :
  motor_shields {
    MotorShield(0x61), //wheels 0 and 1; token arm
    MotorShield(0x62), //wheels 2 and 4; sorting plate 
    MotorShield(0x60)  //magnet
  },
  flags(Flag::NONE),
  pid_terms {
    //Proportional //Integral    //Derivitave  //Accum.  //Last error
    {Fixed(0.005), Fixed(0.005), Fixed(0.000), Fixed(0), Fixed(0)}, //x terms
    {Fixed(0.005), Fixed(0.005), Fixed(0.000), Fixed(0), Fixed(0)}, //y terms
    {Fixed(0.025), Fixed(0.005), Fixed(0.000), Fixed(0), Fixed(0)}, //rot terms
  },
  base_speed(Fixed(90)),
  veer_amount(Fixed(10)),
  acceleration(Fixed(10)),
  current_direction(Direction::NONE),
  wheels {
    //Interrupt Pins: 2, 3, 18, 19, 20, 21
    Wheel(motor_shields[0].getMotor(1),  2, 4), //FRONT_LEFT
    Wheel(motor_shields[0].getMotor(2),  3, 5), //BACK_LEFT
    Wheel(motor_shields[1].getMotor(1), 18, 8), //BACK_RIGHT
    Wheel(motor_shields[1].getMotor(2), 19, 9)  //FRONT_RIGHT
  },
  edge_detectors {
    ProximitySensor( 6,  7), //RIGHT(0)
    ProximitySensor( 8,  9), //FRONT(1)
    ProximitySensor(10, 11), //LEFT(2)
    ProximitySensor(12, 14)  //BACK(3)
  },
  line_sensor(),
  debug(true) {  //if we wrap our Serial.prints checking for this we can toggle it more easily than commenting.
    stop();
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
  for(ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();
}

void Robot::checkDestination() {
  for(int i = 0; i < 2; i++) {
    /*//Debug Serial Printing
    Serial.print("current_wheel_pos: ");
    Serial.println(wheels[i].getPosition().getInt());
    Serial.print("target_wheel_pos: ");
    Serial.println(target_wheel_pos[i].getInt());*/
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

void Robot::correctErrors() {
  Fixed xerr, yerr, rerr;
  line_sensor.getLineErrors(&xerr, &yerr, &rerr, current_direction, 7);
  veer(
    //PID CONTROLLER
    //KP * current error     +  KI * accumulated error             +  KD * change in error
    (pid_terms[0][0] * xerr) + (pid_terms[0][1] * pid_terms[0][3]) + (pid_terms[0][2] * (xerr - pid_terms[0][4])), //x correction
    (pid_terms[1][0] * yerr) + (pid_terms[1][1] * pid_terms[1][3]) + (pid_terms[1][2] * (yerr - pid_terms[1][4])), //y correction
    (pid_terms[2][0] * rerr) + (pid_terms[2][1] * pid_terms[2][3]) + (pid_terms[2][2] * (rerr - pid_terms[2][4]))  //rot correction
  );
  pid_terms[0][3] += xerr;
  pid_terms[1][3] += yerr;
  pid_terms[2][3] += rerr;
  pid_terms[0][4]  = xerr;
  pid_terms[1][4]  = yerr;
  pid_terms[2][4]  = rerr;
  if(debug) {
    Serial.print("Time");
    Serial.println(millis());
    reportWheelSpeeds();
  }
}

void Robot::stop() {
  flags &= ~Flag::FOLLOWING_LINE;
  flags &= ~Flag::CENTERING_CROSS;
  flags &= ~Flag::CENTERING_CORNER;
  for(Wheel& w : wheels) w.stop();
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
    if((flags & Flag::FOLLOWING_LINE) != Flag::NONE) correctErrors();
  }
  
  if((dt[2] > 10) ? (last_ran[2] = time) : false) {
    if((flags & Flag::CALIBRATING_LINE) != Flag::NONE) line_sensor.calibrateSensors();
  }
  
  if((dt[3] > 1000) ? (last_ran[3] = time) : false) {
    if((flags & Flag::PRINTING_LINE) != Flag::NONE) line_sensor.printReadings(); 
  }
  
  if((dt[4] > 50) ? (last_ran[4] = time) : false) {
    if((flags & Flag::STOPPING_INT) != Flag::NONE) if(line_sensor.countLinePeaks(1) == 4) stop();//checkEdges();
  }
  
  if((dt[5] > 100) ? (last_ran[5] = time) : false) {
    if((flags & Flag::TRAVEL_TO_DST) != Flag::NONE) checkDestination();
  }
  
  if((dt[6] > 0) ? (last_ran[6] = time) : false) {
    if((flags & Flag::CENTERING_CROSS) != Flag::NONE) centerCross(4);
  }
  
  if((dt[7] > 0) ? (last_ran[7] = time) : false) {
    if((flags & Flag::CENTERING_CORNER) != Flag::NONE) centerCorner(16);
  }
}

void Robot::centerCross(int offset) {
  flags &= ~Flag::FOLLOWING_LINE;
  flags &= ~Flag::CENTERING_CORNER;
  Fixed xerr, yerr, rerr;
  line_sensor.getCrossIntersectionErrors(&xerr, &yerr, &rerr, offset);
  veer(
    //PID CONTROLLER
    //KP * current error     +  KI * accumulated error             +  KD * change in error
    (pid_terms[0][0] * xerr) + (pid_terms[0][1] * pid_terms[0][3]) + (pid_terms[0][2] * (xerr - pid_terms[0][4])), //x correction
    (pid_terms[1][0] * yerr) + (pid_terms[1][1] * pid_terms[1][3]) + (pid_terms[1][2] * (yerr - pid_terms[1][4])), //y correction
    (pid_terms[2][0] * rerr) + (pid_terms[2][1] * pid_terms[2][3]) + (pid_terms[2][2] * (rerr - pid_terms[2][4]))  //rot correction
  );
  pid_terms[0][3] += xerr;
  pid_terms[1][3] += yerr;
  pid_terms[2][3] += rerr;
  pid_terms[0][4]  = xerr;
  pid_terms[1][4]  = yerr;
  pid_terms[2][4]  = rerr;
}

void Robot::centerCorner(int offset) {
  flags &= ~Flag::FOLLOWING_LINE;
  flags &= ~Flag::CENTERING_CROSS;
  Fixed xerr, yerr, rerr;
  line_sensor.getCornerIntersectionErrors(&xerr, &yerr, &rerr, offset);
  veer(
    //PID CONTROLLER
    //KP * current error     +  KI * accumulated error             +  KD * change in error
    (pid_terms[0][0] * xerr) + (pid_terms[0][1] * pid_terms[0][3]) + (pid_terms[0][2] * (xerr - pid_terms[0][4])), //x correction
    (pid_terms[1][0] * yerr) + (pid_terms[1][1] * pid_terms[1][3]) + (pid_terms[1][2] * (yerr - pid_terms[1][4])), //y correction
    (pid_terms[2][0] * rerr) + (pid_terms[2][1] * pid_terms[2][3]) + (pid_terms[2][2] * (rerr - pid_terms[2][4]))  //rot correction
  );
  pid_terms[0][3] += xerr;
  pid_terms[1][3] += yerr;
  pid_terms[2][3] += rerr;
  pid_terms[0][4]  = xerr;
  pid_terms[1][4]  = yerr;
  pid_terms[2][4]  = rerr;
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
  Serial.println(pid_terms[var][term].getDouble());
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

SortBot::SortBot() : SortingSystem(Robot::motor_shields[0].getStepper(200, 2), Robot::motor_shields[2].getMotor(1), Robot::motor_shields[1].getStepper(200, 2)) {}
