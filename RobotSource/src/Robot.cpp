#include "../include/Robot.h"

#include <iostream>

Robot::Robot(Board* b) : platform(b), location(platform->getStart()), current_intersection(-1), int_cam(2), location_cam(1), speed(70) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

Direction Robot::determineDirection(Coord dest) const {
  Coord diff(dest.x - location.x, dest.y - location.y);
  diff 
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
  for(int i = 0; i < 20; i++) int_cam.onLine();
  travel(dir, speed, 2, false);
  //if(dir == Direction::NONE) return;
  //if(dir == Direction::CLOCKWISE) return;
  //if(dir == Direction::COUNTER_CLOCKWISE) return;
  move(dir, speed);
  while(!int_cam.onLine());
  stop();
  std::cout << "stopped at line" << std::endl;
}

bool Robot::followUntilIntersection(Direction dir) {
  std::cout << "following until intersection" << std::endl;
  //if(dir == Direction::NONE) return false;
  //if(dir == Direction::CLOCKWISE) return false;
  //if(dir == Direction::COUNTER_CLOCKWISE) return false;
  followLine(dir);
  for(int i = 0; i < 10; i++) int_cam.onLine();
  double x, y;
  while(!int_cam.atIntersection());// || int_cam.getTokenErrors(&x, &y, 2));
  std::cout << "stopped at intersection" << std::endl;
  stop();
  if(!int_cam.getTokenErrors(&x, &y)) return false;
  return true;
}

bool Robot::tokenSeen() {
  return int_cam.tokenSeen();
}

/*bool Robot::center(bool cross, int offset) {
  static const double x_tol = 0.1;
  static const double y_tol = 0.1;
  double x = x_tol;
  double y = y_tol;
  //if(!int_cam.getTokenErrors(&x, &y, 5)) followUntilIntersection(dir)
  stop();
  if(cross) {
    LineFollower::startCentering(cross, offset);
    while(!int_cam.getTokenErrors(&x, &y, 1));
    //for(int i = 0; i < 100; i++) 
    stop();
    if(!int_cam.getTokenErrors(&x, &y, 1)) {
      LineFollower::startCentering(cross, offset);
      while(!int_cam.getTokenErrors(&x, &y, 1));
      stop();
    }
  }
  else if(!int_cam.getTokenErrors(&x, &y, 1)) return false;
  std::cout << "Done with line follow centering, starting camera centering" << std::endl;
  int iter = 0;
  for(bool found = int_cam.getTokenErrors(&x, &y); (iter++ < 100) && (std::abs(x) >= x_tol || std::abs(y) >= y_tol); found = int_cam.getTokenErrors(&x, &y)) {
    if(!found) continue;
    std::cout << "nudging" << std::endl;
    nudge(Direction::RIGHT, x);
    nudge(Direction::FRONT, y);
  }
 
  std::cout << "Robot.center() Done" << std::endl << std::endl;
  return true;
}
*/
bool Robot::goToIntersection(int int_num) {
  if(!int_cam.atIntersection()) recover();
  if(current_intersection == -1) return false;
  std::vector<int> shortest_route;
  if(!platform->getShortestPath(&shortest_route, current_intersection, int_num)) return false;
  std::cout << std::endl << "in route to " << int_num << std::endl;
  for(int i = 0; i < shortest_route.size(); i++) {
    Coord new_loc = platform->getIntersectionLocation(shortest_route[i]);
    //Direction follow_dir = robot.determineDirection(new_loc);
    std::cout << "going to int " << shortest_route[i] << std::endl;
    //robot.align(follow_dir);
    //robot.followWhileIntersection(follow_dir);
    //robot.followUntilIntersection(follow_dir);
    location = new_loc;
    current_intersection = shortest_route[i];
    //robot.center();
  }
  return true;
}

bool Robot::setCurrentIntersection(int int_num) {
  if(!int_cam.atIntersection()) return false;
  current_intersection = int_num;
  return true;
}

void Robot::recover() {
  return;
}

SortBot::SortBot(Board* b) : Robot(b), control(*this) {}

int SortBot::followPath(std::vector<int>& path, bool sorting) {
  for(int i = 0; i < path.size(); i++) {
    goToIntersection(path[i]);
    //if(sorting) sortToken();
  }
  return 0;
}
