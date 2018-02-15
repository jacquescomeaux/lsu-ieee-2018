#include "Robot.h"

Robot::Robot() {}

//void Robot::move() {}

void Robot::stop() {
  for(auto w : wheels)
}

void Robot::checkEdges() {
  for(auto s : edge_detectors) if(s.edgeDetected()) stop();
}
