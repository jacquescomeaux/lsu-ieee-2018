#include "../include/Camera.h"

Camera::Camera() : Camera("untitled camera") {}

Camera::Camera(std::string n) {
  name = n;
}

std::string Camera::getName() const {
  return name;
}

bool Camera::onLine() const {return true;}

bool Camera::atIntersection() const {return true;}

bool Camera::tokenSeen() const {return false;}

Coord Camera::determineLocation() const {return Coord(0,0);}
