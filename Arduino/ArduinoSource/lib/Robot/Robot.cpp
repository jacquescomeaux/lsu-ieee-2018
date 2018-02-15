#include "Robot.h"

Robot::Robot() :
  KP(0.1f),
  KD(5.0f),
  default_speed(70),
  AFMS {
    Adafruit_MotorShield(0x61),
    Adafruit_MotorShield(0x62),
  },
  wheels {
    Wheel(AFMS[0].getMotor(1)),
    Wheel(AFMS[0].getMotor(2)),
    Wheel(AFMS[1].getMotor(1)),
    Wheel(AFMS[1].getMotor(2)),
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
  } {
  stop();
} 

void Robot::correctErrors() {
  int error = line_sensors[static_cast<int>(current_direction)].getLineError();  
  int adjustment = this->KP * error + this->KD * (error - last_error);
  this->last_error = error;
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed((i<2)?adjustment:-1*adjustment);
}

void Robot::approachSpeed() {
  for(auto w : wheels) w.approachSpeed();
  if(following_line) correctErrors();
}

void Robot::checkEdges() {
  for(auto s : edge_detectors) if(s.edgeDetected()) stop();
}

void Robot::move(Direction dir) {
  move(dir, default_speed);
}

void Robot::move(Direction dir, int speed) {
  this->following_line = false;
  switch(dir) {
    case(Direction::FRONT):
      for(auto w : wheels) w.setSpeed(speed); 
      break;
    case(Direction::BACK):
      for(auto w : wheels) w.setSpeed(-speed);
      break;
    default: stop();
  }
}

void Robot::followLine(Direction dir) {
  followLine(dir, default_speed);
}

void Robot::followLine(Direction dir, int speed) {
  this->following_line = true;
  switch(dir) {
    case(Direction::FRONT):
      for(auto w : wheels) w.setSpeed(speed); 
      break;
    case(Direction::BACK):
      for(auto w : wheels) w.setSpeed(-speed);
      break;
    default: stop();
  }
}

void Robot::stop() {
  for(auto w : wheels) w.stop();
}

SortBot::SortBot() {}

