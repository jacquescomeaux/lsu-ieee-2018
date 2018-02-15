#include "Robot.h"

Robot::Robot() :
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
  //wow
}

/*Robot::Robot() {
  unsigned char pin = 30;
  unsigned char u = 0;
  for(auto s : line_sensors) s = LineSensor((u++)+pin);
}*/

void Robot::approachSpeed() {
  
}

void Robot::checkEdges() {
  for(auto s : edge_detectors) if(s.edgeDetected()) stop();
}

void Robot::move(DIRECTION dir) {

}

void Robot::stop() {
  for(auto w : wheels) w.stop();
}

SortBot::SortBot() {}

