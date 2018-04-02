#include "../include/Robot.h"

#include <iostream>

Robot::Robot() : token_cam(2), location_cam(1) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

void Robot::moveUntilLine(Direction dir, int speed) {
  for(int i = 0; i < 20; i++) token_cam.onLine();
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  move(dir, speed);
  while(!token_cam.onLine());
  stop();
}

void Robot::followUntilIntersection(Direction dir) {
  for(int i = 0; i < 20; i++) token_cam.onLine();
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  followLine(dir);
  //while(token_cam.onLine()) if(token_cam.atIntersection()) break;
  //while(true) token_cam.atIntersection();
  while(!token_cam.atIntersection());
  //std::cout << "stopped at intersection" << std::endl;
  stop();
}

bool Robot::tokenSeen() const {
  return token_cam.tokenSeen();
}

void Robot::center(bool cross, int offset) {
  while(!token_cam.intersectionInFrame()) LineFollower::center(cross, offset);
  while(!token_cam.tokenCentered()) {
    float x = 0;
    float y = 0;
    token_cam.getTokenErrors(&x, &y);
    if(x > 0 ) nudge(Direction::RIGHT, x);
    else if(x < 0) nudge(Direction::LEFT, -x);
    if(y > 0) nudge(Direction::FRONT, y);
    else if(y < 0) nudge(Direction::BACK, -y);
  }
  //LineFollower::center(cross, offset); //do a line following center before we leave to straighten out. Token pickup needs to happen before this tho
  //stop();
  std::cout << "Robot.center() Done" << std::endl;
}

SortBot::SortBot() : control(*this) {}
