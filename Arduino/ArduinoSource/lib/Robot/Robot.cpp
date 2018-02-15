#include "Robot.h"

Robot::Robot() :
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

void Robot::approachSpeed() {}

void Robot::checkEdges() {
  for(auto s : edge_detectors) if(s.edgeDetected()) stop();
}

SortBot::SortBot() {}

