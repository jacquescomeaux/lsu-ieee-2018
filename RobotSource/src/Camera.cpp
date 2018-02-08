#include "../include/Camera.h"

Camera::Camera() {
  this->name = "untitled_camera";
}

Camera::Camera(std::string name) {
  this->name = name;
}

std::string Camera::getName() {
  return name;
}
