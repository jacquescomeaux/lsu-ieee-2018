#include "../include/SortingSystem.h"
#include <iostream>

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
  //you forgot to do yellow
  if ((avS < 80) && (avV < 80)) tokenColor = Color::GRAY;
  else if (avH > 136) {
    if (avS > 141) tokenColor = Color::RED;
    else tokenColor = Color::MAGENTA;
  }
  else if (avS < 66) tokenColor = Color::CYAN;
  else if (avH < 68) tokenColor = Color::GREEN;
  else tokenColor = Color::BLUE;
  
  if(tokenColor == Color::GRAY) std::cout << "Gray Token Detected" << std::endl;
  else if(tokenColor == Color::RED) std::cout << "Red Token Detected" << std::endl;
  else if(tokenColor == Color::MAGENTA) std::cout << "Magenta Token Detected" << std::endl;
  else if(tokenColor == Color::CYAN) std::cout << "Cyan Token Detected" << std::endl;
  else if(tokenColor == Color::GREEN) std::cout << "Green Token Detected" << std::endl;
  else if(tokenColor == Color::BLUE) std::cout << "Blue Token Detected" << std::endl;

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
