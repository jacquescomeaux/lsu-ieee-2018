#include "../include/Robot.h"

Robot::Robot() : token_cam(2), location_cam(0) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

void Robot::moveUntilLine(Direction dir) {
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  move(dir);
  //move(Direction::CLOCKWISE);
/*  while(!token_cam.onLine());*/
  stop();
}

void Robot::followUntilIntersection(Direction dir) {
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  followLine(dir);
  /*while(token_cam.onLine()) if(token_cam.atIntersection()) break;
  */
  while(!atIntersection());
  stop();
}

bool Robot::tokenSeen() const {
  return token_cam.tokenSeen();
}

SortBot::SortBot() : control(*this) {}
