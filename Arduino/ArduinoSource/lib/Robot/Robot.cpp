#include "Robot.h"

Robot::Robot() {}

//void Robot::move() {}

void Robot::stop() {}

void Robot::checkEdges() {
  for(auto s : edge_detectors) if(s.edgeDetected()) stop();
}
