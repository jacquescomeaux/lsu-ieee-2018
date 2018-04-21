#include "../include/Robot.h"

#include <iostream>
#include <cmath>

Robot::Robot(Board* b) :
  platform(b),
  int_cam(1),
  location_cam(2),
  location(platform->getStart()),
  current_intersection(-1),
  base_speed(70),
  velocity(0, 0, 0) {}

Coord Robot::getLocation() const {
  return location_cam.determineLocation();
}

VelocityVector Robot::determineVelocityVector(Coord dest) const {
  VelocityVector diff(dest.x - location.x, dest.y - location.y, 0);
  VelocityVector v(base_speed * cos(diff.angle), base_speed * sin(diff.angle), 0);
  std::cout << "current location: " << location.x << "<-x y->" << location.y << std::endl;
  std::cout << "destination: "<< dest.x << "<-x y->" << dest.y << std::endl;
  std::cout << "diff: " << diff.x << "<-x y->" << diff.y << std::endl;
  std::cout << "v   : "<< v.x << "<-x y->" << v.y << std::endl;
  return v;
}

VelocityVector Robot::resolveDirection(Direction dir) const {
  return resolveDirection(dir, base_speed);
}

VelocityVector Robot::resolveDirection(Direction dir, double speed) const {
  switch(dir) {
    case(Direction::FRONT): return VelocityVector(0, speed, 0); break;
    case(Direction::BACK): return VelocityVector(0, -1 * speed, 0); break;
    case(Direction::LEFT): return VelocityVector(-1 * speed, 0, 0); break;
    case(Direction::RIGHT): return VelocityVector(speed, 0, 0); break;
    case(Direction::FRONT_RIGHT): return VelocityVector(0.5 * sqrt(2) * speed, 0.5 * sqrt(2) * speed, 0); break;
    case(Direction::FRONT_LEFT): return VelocityVector(-0.5 * sqrt(2) * speed, 0.5 * sqrt(2) * speed, 0); break;
    case(Direction::BACK_RIGHT): return VelocityVector(0.5 * sqrt(2) * speed, -0.5 * sqrt(2) * speed, 0); break;
    case(Direction::BACK_LEFT): return VelocityVector(-0.5 * sqrt(2) * speed, -0.5 * sqrt(2) * speed, 0); break;
    case(Direction::CLOCKWISE): return VelocityVector(0, 0, -1 * speed); break;
    case(Direction::COUNTER_CLOCKWISE): return VelocityVector(0, 0, speed); break;
    default: return VelocityVector(0, 0, 0); break;
  }
}

void Robot::setSpeed(int s) {
  base_speed = s;
}

int Robot::getSpeed() const {
  return base_speed;
}

void Robot::adjustSpeed(int s) {
  base_speed += s;
}

void Robot::move(Direction dir) const {
  std::cout << "resolving direction" << std::endl;
  VelocityVector v = resolveDirection(dir);
  std::cout << "x" << v.x << "y" << v.y << "rot" << v.rot << "mag" << v.magnitude << "angle" << v.angle << "offset" << v.offset << std::endl;
  Drivetrain::move(resolveDirection(dir));
}

void Robot::nudge(Direction dir, double dist) {
  Drivetrain::nudge(resolveDirection(dir), dist);
}

void Robot::travel(Direction dir, double speed, double dist, bool stopping) {
  Drivetrain::travel(resolveDirection(dir, speed), dist, stopping);
}

void Robot::align(Direction dir, int range) const {
  LineFollower::align(resolveDirection(dir), range);
} 

void Robot::followLine(Direction dir) const {
  std::cout << "resolving direction" << std::endl;
  VelocityVector v = resolveDirection(dir);
  std::cout << "x" << v.x << "y" << v.y << "rot" << v.rot << "mag" << v.magnitude << "angle" << v.angle << "offset" << v.offset << std::endl;
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
  return int_cam.onLine();
}

bool Robot::followUntilIntersection(Direction dir) {
  if(dir == Direction::NONE) return false;
  if(dir == Direction::CLOCKWISE) return false;
  if(dir == Direction::COUNTER_CLOCKWISE) return false;
  return followUntilIntersection(resolveDirection(dir));
}

bool Robot::followUntilIntersection(VelocityVector v) {
  std::cout << "following until intersection" << std::endl;
  LineFollower::followLine(v, 2);
  for(int i = 0; i < 5; i++) int_cam.onLine();
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

bool Robot::followWhileIntersection(VelocityVector v) {
  std::cout << "following while intersection" << std::endl;
  LineFollower::followLine(v, 2);
  for(int i = 0; i < 5; i++) int_cam.onLine();
  while(int_cam.atIntersection(false));
  stop();
  std::cout << "intersection out of view" << std::endl;
  return int_cam.atIntersection(true);
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
  //LineFollower::center();
  std::cout << "Done with line follow centering, starting camera centering" << std::endl;
  int iter = 0;
  if(!int_cam.atIntersection(true)) return false;
  for(bool found = int_cam.getTokenErrors(&x, &y); (iter++ < 100) && (std::abs(x) >= x_tol || std::abs(y) >= y_tol); found = int_cam.getTokenErrors(&x, &y)) {
    if(!found) continue;
    //std::cout << "nudging" << std::endl;
    nudge(Direction::RIGHT, x);
    nudge(Direction::FRONT, y);
  }
  std::cout << "Robot.center() Done" << std::endl << std::endl;
  return int_cam.atIntersection(true);
}

bool Robot::findIntersection(VelocityVector v) {
  for(double speed_scalar = 1; speed_scalar > 0.3; speed_scalar -= 0.1) {
    Drivetrain::travel(v, -1.2, true);
    if(followUntilIntersection(speed_scalar * v)) return true;
  }
  return false;
  /*for(double backtrack_amount = 1.2; backtrack_amount > 0; backtrack_amount -= 0.1) {
    Drivetrain::travel(v, -1 * backtrack_amount, false);
    if(followUntilIntersection(v)) return true;
  }
  return false;
*/}

bool Robot::goToIntersection(int int_num) {
  if(!int_cam.atIntersection(true)) {
  std::cout << "Calling recover\n";
  recover();
  }
  if(current_intersection == -1) {
    std::cout << "Error: Current intersection is -1\n";
    return false;
  }
  std::vector<int> shortest_route;
  if(!platform->getShortestPath(&shortest_route, current_intersection, int_num)) return false;
  std::cout << std::endl << "in route to " << int_num << std::endl;
  for(unsigned int i = 0; i < shortest_route.size(); i++) {
    Coord new_loc = platform->getIntersectionLocation(shortest_route[i]);
    double distance = 12 * location.dist(new_loc);
    std::cout << "distance is " << distance << std::endl;
    VelocityVector follow_vect = determineVelocityVector(new_loc);
    std::cout << "going to int " << shortest_route[i] << std::endl;
    LineFollower::followLine(follow_vect, 2);
    Drivetrain::travel(follow_vect, distance/2, true);
    LineFollower::align(follow_vect, 2);
    if(!followUntilIntersection(follow_vect)) while(!findIntersection(follow_vect));
    location = new_loc;
    current_intersection = shortest_route[i];
    if(!center()) return false;
  }
  return true;
}

bool Robot::setCurrentIntersection(int int_num) {
  if(!int_cam.atIntersection(true)) return false;
  current_intersection = int_num;
  location = platform->getIntersectionLocation(int_num);
  return true;
}

void Robot::recover() {
  return;
}

SortBot::SortBot(Board* b) : Robot(b) {}

int SortBot::followPath(std::vector<int>& path, bool sorting) {
  setSpeed(80);
  int visited;
  for(unsigned int i = 0; i < path.size(); i++) {
    if(!goToIntersection(path[i])) break;
    if(sorting) sortToken();
    visited = i + 1;
  }
  return visited;
}
