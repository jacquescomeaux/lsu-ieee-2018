#include "../include/Robot.h"

Robot::Robot() {
  serialInit();
}

Robot::~Robot() {
  serialQuit();
}

Coord Robot::getLocation() {
  return location;
}
    
void Robot::setLocation(Coord c) {
  location = c;
} 
