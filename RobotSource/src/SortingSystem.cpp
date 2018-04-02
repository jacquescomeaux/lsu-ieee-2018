#include "../include/SortingSystem.h"

SortingSystem::SortingSystem() {}

void SortingSystem::pickUpToken() {
  token_arm.pickUpToken();
}

Color SortingSystem::checkTokenColor() const {
  return color_sensor.getColor();
}

void SortingSystem::sortToken() {
}

void SortingSystem::dropTokenStack(Color c) {}
