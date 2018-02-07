#include "Robot.h"

Robot::Robot() {}

Coord Robot::getLocation() {
  return location;
}
    
void Robot::setLocation(Coord c) {
  location = c;
} 
