#include "../include/Robot.h"

#include <iostream>

Robot::Robot() : int_cam(1), location_cam(2) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

void Robot::moveUntilLine(Direction dir, int speed) {
  for(int i = 0; i < 20; i++) int_cam.onLine();
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  move(dir, speed);
  while(!int_cam.onLine());
  stop();
}

void Robot::followUntilIntersection(Direction dir) {
  for(int i = 0; i < 20; i++) int_cam.onLine();
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  followLine(dir);
  //while(int_cam.onLine()) if(int_cam.atIntersection()) break;
  //while(true) int_cam.atIntersection();
  while(!int_cam.atIntersection());
  //std::cout << "stopped at intersection" << std::endl;
  stop();
  //nudge(dir, -0.5);
}

bool Robot::tokenSeen() const {
  return int_cam.tokenSeen();
}

void Robot::center(bool cross, int offset) {
/* int reset = 10; //number of times to try to reset robot on intersection before we need to handle it
  int fix = 0;
  while(!int_cam.intersectionInFrame()) {
    LineFollower::center(cross, offset);
    reset--;
    if(reset == 0) {
    }
*/
  float x = 0;
  float y = 0;
  LineFollower::startCentering(cross, offset);
  while(!int_cam.intersectionInFrame());
  stop();
  while(!int_cam.tokenCentered()) {
    int_cam.getTokenErrors(&x, &y);
    if(x > 0 ) nudge(Direction::RIGHT, x);
    else if(x < 0) nudge(Direction::LEFT, -x);
    if(y > 0) nudge(Direction::FRONT, y);
    else if(y < 0) nudge(Direction::BACK, -y);
  }
  std::cout << "Robot.center() Done" << std::endl;
}

SortBot::SortBot() : control(*this) {}
