#include "../include/Camera.h"

Camera::Camera() : Camera("untitled camera") {}

Camera::Camera(std::string name) {
  this->name = name;
}

std::string Camera::getName() const {
  return name;
}

bool Camera::onLine() const {return false;}

bool Camera::getIntersection() const {return true;}
