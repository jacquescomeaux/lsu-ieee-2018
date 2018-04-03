#include "../include/SortingSystem.h"

SortingSystem::SortingSystem() {}

void SortingSystem::pickUpToken() {
  token_arm.pickUpToken();
}

Color SortingSystem::checkTokenColor() const {
  static int c = 0;
  if(++c > 7) c = 1;
  return static_cast<Color>(c);//color_sensor.getColor();
}

void SortingSystem::sortToken(Color c) {
  transmitChar('r');
  transmitColor(c);
}

void SortingSystem::dropTokenStack(Color c) {}
