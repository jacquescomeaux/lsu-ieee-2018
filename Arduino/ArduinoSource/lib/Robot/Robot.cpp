#include <Robot.h>

Robot::Robot() :
  KP(0.07f),
  KD(0.0f),
  default_speed(60),
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
    ProximitySensor(),
    ProximitySensor(),
    ProximitySensor(),
    ProximitySensor()
  },
  line_sensors {
    LineSensor(30),
    LineSensor(33),
    LineSensor(36),
    LineSensor(39),
    LineSensor(42),
    LineSensor(45),
    LineSensor(48),
    LineSensor(51)
  },
  following_line(false),
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
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((1 - (2 * (i % 2))) * speed);
      current_direction = Direction::LEFT;
      break;
    case(Direction::RIGHT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(((2 * (i % 2)) - 1) * speed);
      current_direction = Direction::RIGHT;
      break;
    case(Direction::FRONT_LEFT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((1 - (i % 2)) * speed);
      current_direction = Direction::FRONT_LEFT;
      break;
    case(Direction::FRONT_RIGHT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((i % 2) * speed);
      current_direction = Direction::FRONT_RIGHT;
      break;
    case(Direction::BACK_LEFT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(-1 * (i % 2) * speed);
      current_direction = Direction::BACK_LEFT;
      break;
    case(Direction::BACK_RIGHT):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(((i % 2) - 1) * speed);
      current_direction = Direction::BACK_RIGHT;
      break;
    case(Direction::CLOCKWISE):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed(((2 * (i / 2)) - 1) * speed);
      current_direction = Direction::CLOCKWISE;
      break;
    case(Direction::COUNTER_CLOCKWISE):
      for(int i = 0; i < 4; i++) wheels[i].setSpeed((1 - (2 * (i / 2))) * speed);
      current_direction = Direction::COUNTER_CLOCKWISE;
      break;
    default: stop();
  }
}

void Robot::correctErrors() {
//  if(!following_line) return;
  //Serial.println("CORRECTIGERROS"); 
  int error = line_sensors[0].getLineError();//static_cast<int>(current_direction)].getLineError();  
  //Serial.print("ERROR=");
  //Serial.println(error);
  line_sensors[0].printReadings(); 
  int adjustment = KP * error + KD * (error - last_error);
  this->last_error = error;
  //for(int i = 0; i < 4; i++) wheels[i].adjustSpeed((i<2)?adjustment:-adjustment);
}

void Robot::approachSpeed() {
  for(Wheel& w : wheels) w.approachSpeed();
  if(following_line) correctErrors();
}

void Robot::checkEdges() {
  for(ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();
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
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed((i<2)?-5:5);
}

void Robot::veerRight() {
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed(!(i<2)?-5:5);
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

SortBot::SortBot() {}

