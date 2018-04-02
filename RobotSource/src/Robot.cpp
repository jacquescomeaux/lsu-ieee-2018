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
  int reset = 10; //number of times to try to reset robot on intersection before we need to handle it
  int fix = 0;
  while(!token_cam.intersectionInFrame()) {
    LineFollower::center(cross, offset);
    reset--;
    if(reset == 0 && !cross) { //this is sort of a failed hail-mary attempt at getting back where we need to be. We can make it smarter but I'd rather not need it.
      Direction dir;
      if(fix == 0) dir = Direction::FRONT;
      else if (fix == 1) dir = Direction::LEFT;
      else if (fix == 2) dir = Direction::BACK;
      else if (fix == 3) dir = Direction::RIGHT;

     if(fix < 2) travel(dir, 70, 1, false);
     else travel(dir, 70, 2, false); //move twice as much in the reverse directions to compensate
      reset = 10; //number of times to look for intersection after attempting a fix
      fix++;
    }
  if(fix >= 3) fix = 0;
  }

  float x = 0;
  float y = 0;
  while(token_cam.intersectionInFrame() && !token_cam.tokenCentered()) {
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
