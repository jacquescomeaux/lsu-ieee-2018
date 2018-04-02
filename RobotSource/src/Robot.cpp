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
  //LineFollower::center(cross, offset);
  float x = 0;
  float y = 0;
  while(token_cam.intersectionInFrame() && !token_cam.tokenCentered()) {
    token_cam.getTokenErrors(&x, &y);
    std::cout << "travelling by " << x << "in x direction" << std::endl;
    if(x > 0) nudge(Direction::RIGHT, x);
    else nudge(Direction::LEFT, abs(x));
    std::cout << "travelling by " << y << "in y direction" << std::endl; 
    if(y > 0) nudge(Direction::FRONT, y);
    else nudge(Direction::BACK, abs(y));
  }
  std::cout << "Robot is done trying to center on intersection" << std::endl;
}

SortBot::SortBot() : control(*this) {}
