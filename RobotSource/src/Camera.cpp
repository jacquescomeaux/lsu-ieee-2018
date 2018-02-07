#include "../include/Camera.h"

Camera::Camera() {
  name = "untitled_camera";
}

Camera::Camera(std::string name) {
  this->name = name;
}

std::string getName() {
  return name;
}
