#include "../include/Robot.h"

#include <iostream>
#include <cmath>

Robot::Robot(Board* b) :
  platform(b),
  int_cam(2),
  location_cam(1),
  location(platform->getStart()),
  current_intersection(-1),
  base_speed(70),
  velocity(0, 0, 0) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

VelocityVector Robot::determineVelocityVector(Coord dest) const {
  VelocityVector diff(dest.x - location.x, dest.y - location.y, 0);
  return diff;
}

VelocityVector Robot::resolveDirection(Direction dir) const {
  switch(dir) {
    case(Direction::FRONT): return VelocityVector(0, base_speed, 0); break;
    case(Direction::BACK): return VelocityVector(0, -1 * base_speed, 0); break;
    case(Direction::LEFT): return VelocityVector(-1 * base_speed, 0, 0); break;
    case(Direction::RIGHT): return VelocityVector(base_speed, 0, 0); break;
    case(Direction::FRONT_RIGHT): return VelocityVector(0.5 * sqrt(2) * base_speed, 0.5 * sqrt(2) * base_speed, 0); break;
    case(Direction::FRONT_LEFT): return VelocityVector(-0.5 * sqrt(2) * base_speed, 0.5 * sqrt(2) * base_speed, 0); break;
    case(Direction::BACK_RIGHT): return VelocityVector(0.5 * sqrt(2) * base_speed, -0.5 * sqrt(2) * base_speed, 0); break;
    case(Direction::BACK_LEFT): return VelocityVector(-0.5 * sqrt(2) * base_speed, -0.5 * sqrt(2) * base_speed, 0); break;
    case(Direction::CLOCKWISE): return VelocityVector(0, 0, -1 * base_speed); break;
    case(Direction::COUNTER_CLOCKWISE): return VelocityVector(0, 0, base_speed); break;
    default: return VelocityVector(0, 0, 0); break;
  }
}

void Robot::setSpeed(int s) {
  base_speed = s;
}

void Robot::move(Direction dir) const {
  Drivetrain::move(resolveDirection(dir));
}

void Robot::nudge(Direction dir, double dist) {
  Drivetrain::nudge(resolveDirection(dir), dist);
}

void Robot::travel(Direction dir, double dist, bool stopping) {
  Drivetrain::travel(resolveDirection(dir), dist, stopping);
}

void Robot::followLine(Direction dir) const {
  LineFollower::followLine(resolveDirection(dir), 2);
}

bool Robot::moveUntilLine(Direction dir) {
  if(dir == Direction::NONE) return false;
  if(dir == Direction::CLOCKWISE) return false;
  if(dir == Direction::COUNTER_CLOCKWISE) return false;
  return moveUntilLine(resolveDirection(dir));
}

bool Robot::moveUntilLine(VelocityVector v) {
  std::cout << "following until line" << std::endl;
  for(int i = 0; i < 5; i++) int_cam.onLine();
  Drivetrain::travel(v, 2, false);
  Drivetrain::move(v);
  while(!int_cam.onLine());
  stop();
  std::cout << "stopped at line" << std::endl;
}

bool Robot::followUntilIntersection(Direction dir) {
  if(dir == Direction::NONE) return false;
  if(dir == Direction::CLOCKWISE) return false;
  if(dir == Direction::COUNTER_CLOCKWISE) return false;
  return followUntilIntersection(resolveDirection(dir));
}

bool Robot::followUntilIntersection(VelocityVector v) {
  std::cout << "following until intersection" << std::endl;
  LineFollower::followLine(v);
  for(int i = 0; i < 5; i++) int_cam.onLine();
  double x, y;
  while(!int_cam.atIntersection(false));
  stop();
  std::cout << "stopped at intersection" << std::endl;
  return int_cam.atIntersection(true);
}

bool Robot::followWhileIntersection(Direction dir) {
  if(dir == Direction::NONE) return false;
  if(dir == Direction::CLOCKWISE) return false;
  if(dir == Direction::COUNTER_CLOCKWISE) return false;
  return followWhileIntersection(resolveDirection(dir));
}

bool Robot::tokenSeen() {
  return int_cam.tokenSeen();
}

bool Robot::center() {
  static const double x_tol = 0.1;
  static const double y_tol = 0.1;
  double x = x_tol;
  double y = y_tol;
  if(!int_cam.atIntersection(true)) return false;
  LineFollower::center();
  std::cout << "Done with line follow centering, starting camera centering" << std::endl;
  int iter = 0;
  if(!int_cam.atIntersection(true)) return false;
  for(bool found = int_cam.getTokenErrors(&x, &y); (iter++ < 100) && (std::abs(x) >= x_tol || std::abs(y) >= y_tol); found = int_cam.getTokenErrors(&x, &y)) {
    if(!found) continue;
    std::cout << "nudging" << std::endl;
    nudge(Direction::RIGHT, x);
    nudge(Direction::FRONT, y);
  }
  std::cout << "Robot.center() Done" << std::endl << std::endl;
  return int_cam.atIntersection(true);
}

bool Robot::goToIntersection(int int_num) {
  if(!int_cam.atIntersection(true)) recover();
  if(current_intersection == -1) return false;
  std::vector<int> shortest_route;
  if(!platform->getShortestPath(&shortest_route, current_intersection, int_num)) return false;
  std::cout << std::endl << "in route to " << int_num << std::endl;
  for(int i = 0; i < shortest_route.size(); i++) {
    Coord new_loc = platform->getIntersectionLocation(shortest_route[i]);
    VelocityVector follow_vect = determineVelocityVector(new_loc);
    std::cout << "going to int " << shortest_route[i] << std::endl;
    LineFollower::align(follow_vect, 2);
    followWhileIntersection(follow_vect);
    followUntilIntersection(follow_vect);
    location = new_loc;
    current_intersection = shortest_route[i];
    if(!robot.center()) return false;
  }
  return true;
}

bool Robot::setCurrentIntersection(int int_num) {
  if(!int_cam.atIntersection(true)) return false;
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
    if(sorting) sortToken();
  }
  return 0;
}
