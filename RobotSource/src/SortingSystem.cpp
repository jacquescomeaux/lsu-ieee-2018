#include "../include/SortingSystem.h"

SortingSystem::SortingSystem() : token_cam(0) {}

void SortingSystem::pickUpToken() {
  transmitChar('p');
  receiveChar();
}

Color SortingSystem::checkTokenColor() const {
  static int c = 0;
  if(++c > 7) c = 1;
  return static_cast<Color>(c);//color_sensor.getColor();
}

void SortingSystem::storeToken(Color c) const {
  transmitChar('r');
  transmitColor(c);
}

void SortingSystem::sortToken() {
  pickUpToken();
  storeToken(checkTokenColor());
}

void SortingSystem::dropTokenStack(Color c) {}
