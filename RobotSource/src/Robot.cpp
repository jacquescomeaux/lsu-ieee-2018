#include "../include/Robot.h"

Robot::Robot() {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

void Robot::moveUntilLine(Direction dir) const {
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  move(dir);
  while(!token_cam.onLine());
  stop();
}

void Robot::followUntilIntersection(Direction dir) const {
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  followLine(dir);
  while(token_cam.onLine()) if(token_cam.atIntersection()) break;
  stop();
}

void Robot::center() const {}

bool Robot::tokenSeen() const {
  return token_cam.tokenSeen();
}

SortBot::SortBot() : control(*this) {}
