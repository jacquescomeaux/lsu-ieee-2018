#include "../include/SortingSystem.h"

SortingSystem::SortingSystem() : token_cam(0) {}

void SortingSystem::pickUpToken() {
  transmitChar('p');
  receiveChar();
}

Color SortingSystem::checkTokenColor() {
  std::vector<double> hvs = token_cam.readToken();
  
  double avH = hvs[0];
  double avV = hvs[1];
  double avS = hvs[2];
  
  Color tokenColor;
  
  if ((avS < 80) && (avV < 80)) tokenColor = Color::GRAY;
  else if (avH > 136) {
    if (avS > 141) tokenColor = Color::RED;
    else tokenColor = Color::MAGENTA;
  }
  else if (avS < 66) tokenColor = Color::CYAN;
  else if (avH < 68) tokenColor = Color::GREEN;
  else tokenColor = Color::BLUE;

  return tokenColor;

  /* static int c = 0;
  if(++c > 7) c = 1;
  return static_cast<Color>(c);*/
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
