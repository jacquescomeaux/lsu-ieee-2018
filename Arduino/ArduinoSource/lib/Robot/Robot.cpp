#include "Robot.h"

Robot::Robot() : line_sensors{LineSensor(30), LineSensor(33), LineSensor(36), LineSensor(39), LineSensor(42), LineSensor(45), LineSensor(48), LineSensor(51)} {}

//void Robot::move() {}

void Robot::stop() {
  for(auto w : wheels)
}

void Robot::approachSpeed() {}

void Robot::checkEdges() {
  for(auto s : edge_detectors) if(s.edgeDetected()) stop();
}

SortBot::SortBot() {}

