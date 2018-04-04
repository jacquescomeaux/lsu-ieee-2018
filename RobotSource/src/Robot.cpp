#include "../include/Robot.h"

#include <iostream>

Robot::Robot() : int_cam(2), location_cam(1), speed(70) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

void Robot::setSpeed(int s) const {
  speed = s;
}

void Robot::moveUntilLine(Direction dir, int speed) {
  std::cout << "following until line" << std::endl;
  travel(dir, speed, 1, false);
  for(int i = 0; i < 20; i++) int_cam.onLine();
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  move(dir, speed);
  while(!int_cam.onLine());
  stop();
  std::cout << "stopped at line" << std::endl;
}

void Robot::followUntilIntersection(Direction dir) {
  std::cout << "following until intersection" << std::endl;
  for(int i = 0; i < 20; i++) int_cam.onLine();
  travel(dir, speed, 1, false);
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  followLine(dir);
  //while(int_cam.onLine()) if(int_cam.atIntersection()) break;
  //while(true) int_cam.atIntersection();
  while(!int_cam.atIntersection());
  std::cout << "stopped at intersection" << std::endl;
  stop();
  //nudge(dir, -0.5);
}

bool Robot::tokenSeen() {
  return int_cam.tokenSeen();
}

void Robot::center(bool cross, int offset) {
  float x = 0;
  float y = 0;

  LineFollower::startCentering(cross, offset);
  /*while(int_cam.tokenSeen() && !int_cam.tokenCentered()) {
    std::cout << "nudging" << std::endl;
    int_cam.getTokenErrors(&x, &y);
    nudge(Direction::RIGHT, x);
    nudge(Direction::FRONT, y);
  */while(!int_cam.intersectionInFrame());
  stop();
  std::cout << "Done with line follow centering, starting camera centering" << std::endl;
  for(int i = 0; i < 5; i++) if(int_cam.tokenSeen()) {
  //while(int_cam.tokenSeen() && !int_cam.tokenCentered()) {
    int_cam.getTokenErrors(&x, &y);
    std::cout << "Token Errors: X: " << x << " Y: " << y << std::endl;
    if(x > 0 ) nudge(Direction::RIGHT, x);
    else if(x < 0) nudge(Direction::LEFT, -x);
    if(y > 0) nudge(Direction::FRONT, y);
    else if(y < 0) nudge(Direction::BACK, -y);
    if (x == 0 && y == 0) break;
    //if(int_cam.tokenCentered()) break;
  }
  //stop();
  std::cout << "Robot.center() Done" << std::endl << std::endl;
}

SortBot::SortBot() : control(*this) {}
