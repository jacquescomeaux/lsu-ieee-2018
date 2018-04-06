#include "../include/Robot.h"

#include <iostream>

Robot::Robot() : int_cam(0), location_cam(1), speed(70) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

void Robot::followLine(Direction dir) const {
  LineFollower::followLine(dir, speed);
}

void Robot::setSpeed(int s) {
  speed = s;
  Drivetrain::setSpeed(s);
}

void Robot::moveUntilLine(Direction dir, int speed) {
  std::cout << "following until line" << std::endl;
  followLine(dir);
  for(int i = 0; i < 20; i++) int_cam.onLine();
  travel(dir, speed, 2, false);
  if(dir == Direction::NONE) return;
  if(dir == Direction::CLOCKWISE) return;
  if(dir == Direction::COUNTER_CLOCKWISE) return;
  move(dir, speed);
  while(!int_cam.onLine());
  stop();
  std::cout << "stopped at line" << std::endl;
}

bool Robot::followUntilIntersection(Direction dir) {
  std::cout << "following until intersection" << std::endl;
  if(dir == Direction::NONE) return false;
  if(dir == Direction::CLOCKWISE) return false;
  if(dir == Direction::COUNTER_CLOCKWISE) return false;
  followLine(dir);
  for(int i = 0; i < 10; i++) int_cam.onLine();
  float x, y;
  while(!int_cam.atIntersection());// || int_cam.getTokenErrors(&x, &y, 2));
  std::cout << "stopped at intersection" << std::endl;
  stop();
  if(!int_cam.getTokenErrors(&x, &y)) return false;
  return true;
}

bool Robot::tokenSeen() {
  return int_cam.tokenSeen();
}

bool Robot::center(bool cross, int offset) {
  static const float x_tol = 0.1;
  static const float y_tol = 0.1;
  float x = x_tol;
  float y = y_tol;
  //if(!int_cam.getTokenErrors(&x, &y, 5)) followUntilIntersection(dir)
  stop();
  if(cross) {
    LineFollower::startCentering(cross, offset);
    while(!int_cam.getTokenErrors(&x, &y, 1));
    stop();
  }
  else if(!int_cam.getTokenErrors(&x, &y, 1)) return false;
  std::cout << "Done with line follow centering, starting camera centering" << std::endl;
  for(bool found = int_cam.getTokenErrors(&x, &y); std::abs(x) >= x_tol || std::abs(y) >= y_tol; found = int_cam.getTokenErrors(&x, &y)) {
    if(!found) continue;
    std::cout << "nudging" << std::endl;
//    nudge(Direction::RIGHT, x);
  //  nudge(Direction::FRONT, y);
    if(x > 0 ) nudge(Direction::RIGHT, x);
    else if(x < 0) nudge(Direction::LEFT, -x);
    if(y > 0) nudge(Direction::FRONT, y);
    else if(y < 0) nudge(Direction::BACK, -y);
  }
 
  /*while(int_cam.tokenSeen() && !int_cam.tokenCentered()) {
    std::cout << "nudging" << std::endl;
    int_cam.getTokenErrors(&x, &y);
    nudge(Direction::RIGHT, x);
    nudge(Direction::FRONT, y);
  *//*while(!int_cam.intersectionInFrame());
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
  */
  std::cout << "Robot.center() Done" << std::endl << std::endl;
  return true;
}

SortBot::SortBot() : control(*this) {}
