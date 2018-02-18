#include "../include/Robot.h"

Robot::Robot() {}
//Robot::Robot() : control(*this) {}

bool Robot::tokenSeen() const {return false;}

void Robot::center() const {}

SortBot::SortBot() : control(*this) {}

/*Coord Robot::getLocation() const {
  return location;
}*/
