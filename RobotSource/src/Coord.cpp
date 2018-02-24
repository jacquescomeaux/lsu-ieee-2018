#include "../include/Coord.h"

#include <cmath>

Coord::Coord(float x, float y) {
  this->x = x;
  this->y = y;
}

float Coord::dist(Coord c) const {
  return std::sqrt(std::pow((x-c.x),2)+std::pow((y-c.y),2));
}
