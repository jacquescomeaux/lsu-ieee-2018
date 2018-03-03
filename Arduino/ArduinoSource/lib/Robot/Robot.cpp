#include <Robot.h>

Robot::Robot() :
  KP(0.03f),
  KD(0.00f),
  default_speed(90),
  motor_shields {
    MotorShield(0x61),
    MotorShield(0x62)
  },
  wheels {
    Wheel(motor_shields[0].getMotor(1)),
    Wheel(motor_shields[0].getMotor(2)),
    Wheel(motor_shields[1].getMotor(1)),
    Wheel(motor_shields[1].getMotor(2))
  },
  edge_detectors {
    ProximitySensor(5, 6),
    ProximitySensor(0, 0),
    ProximitySensor(0, 0),
    ProximitySensor(0, 0)
  },
  line_sensors {
    LineSensor(30, 31, 32),
    LineSensor(33, 34, 35),
    //LineSensor(36, 37, 38),
    //LineSensor(39, 40, 41),
    //LineSensor(42, 43, 44),
    //LineSensor(45, 46, 47),
    //LineSensor(48, 49, 50),
    //LineSensor(51, 52, 53)
  },
  following_line(false),
  calibrating(false),
  reading_sensors(false),
  edges(false),
  current_direction(Direction::FRONT),
  last_error(0) {
  stop();
} 

void Robot::setWheelSpeeds(Direction dir, int speed) {
  switch(dir) {
    case(Direction::FRONT):
      for(Wheel& w : wheels) w.setSpeed(speed); 
      current_direction = Direction::FRONT;
      break;
    case(Direction::BACK):
      for(Wheel& w : wheels) w.setSpeed(-speed);
      current_direction = Direction::BACK;
      break;
    case(Direction::LEFT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((i%2)?speed:-speed);
      current_direction = Direction::LEFT;
      break;
    case(Direction::RIGHT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(!(i%2)?speed:-speed);
      current_direction = Direction::RIGHT;
      break;
    case(Direction::FRONT_LEFT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((i%2)?speed:0);
      current_direction = Direction::FRONT_LEFT;
      break;
    case(Direction::FRONT_RIGHT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(!(i%2)?speed:0);
      current_direction = Direction::FRONT_RIGHT;
      break;
    case(Direction::BACK_LEFT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((i%2)?0:-speed);
      current_direction = Direction::BACK_LEFT;
      break;
    case(Direction::BACK_RIGHT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(!(i%2)?0:-speed);
      current_direction = Direction::BACK_RIGHT;
      break;
    case(Direction::CLOCKWISE):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(!(i/2)?speed:-speed);
      current_direction = Direction::CLOCKWISE;
      break;
    case(Direction::COUNTER_CLOCKWISE):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((i/2)?speed:-speed);
      current_direction = Direction::COUNTER_CLOCKWISE;
      break;
    default: stop();
  }
}

void Robot::correctErrors() {
  int error = line_sensors[static_cast<int>(current_direction)].getLineError();  
  int adjustment = KP * error + KD * (error - last_error);
  last_error = error;
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed((i<2)?adjustment:-adjustment);
}

void Robot::approachSpeed() {
  for(Wheel& w : wheels) w.approachSpeed();
  if(following_line) correctErrors();
  if(calibrating) for(LineSensor& l : line_sensors) l.calibrateSensors();
  if(reading_sensors) line_sensors[static_cast<int>(current_direction)].printReadings(); 
}

void Robot::checkEdges() {
  int time = millis();
  if(time - last_ran < 10) return;
  last_ran = time;
  //for(const ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();
  
  if(edge_detectors[0].edgeDetected()) stop();
  Serial.println(edge_detectors[0].getProximity());
}

void Robot::move(Direction dir) {
  //Serial.println("call to move");//
  move(dir, default_speed);
}

void Robot::move(Direction dir, int speed) {
  following_line = false;
  setWheelSpeeds(dir, speed);
}

void Robot::followLine(Direction dir) {
  //Serial.println("call to follow");//
  followLine(dir, default_speed);
}

void Robot::followLine(Direction dir, int speed) {
  following_line = true;
  setWheelSpeeds(dir, speed);
}

void Robot::veerLeft() {
  for(int i = 0; i < 4; i++) wheels[i].incrementSpeed((i<2)?-10:10);
}

void Robot::veerRight() {
  for(int i = 0; i < 4; i++) wheels[i].incrementSpeed(!(i<2)?-10:10);
}

void Robot::speedUp() {
  for(Wheel& w : wheels) w.adjustSpeed(5);
}
void Robot::slowDown() {
  for(Wheel& w : wheels) w.adjustSpeed(-5);
}

void Robot::stop() {
  following_line = false;
  for(Wheel& w : wheels) w.stop();
}

void Robot::toggleCalibration() {
  calibrating = !calibrating;
  if(calibrating) Serial.println("Begin Calibration");
  else Serial.println("End Calibration");
}

void Robot::toggleSensorsOutput() {
  reading_sensors = !reading_sensors;
  if(calibrating) Serial.println("Begin Output");
  else Serial.println("End Output");
}

void Robot::toggleEdgeOutput() {
  edges = !edges;
  if(edges) Serial.println("Begin Output edges");
  else Serial.println("End Output edges");
}

void Robot::adjustDefaultSpeed(int adjustment) {
  default_speed += adjustment;
  Serial.print("Speed = ");
  Serial.println(default_speed);
}

void Robot::adjustKP(float adjustment) {
  KP += adjustment;
  Serial.print("KP = ");
  Serial.println(KP);
}

void Robot::adjustKD(float adjustment) {
  KD += adjustment;
  Serial.print("KD = ");
  Serial.println(KD);
}

SortBot::SortBot() {}

