#include "../include/Coord.h"

#include <cmath>

Coord::Coord(double x, double y) {
  this->x = x;
  this->y = y;
}

double Coord::dist(Coord c) const {
  return std::sqrt(std::pow((x-c.x),2)+std::pow((y-c.y),2));
}
