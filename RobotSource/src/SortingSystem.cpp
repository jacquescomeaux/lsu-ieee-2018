#include "../include/SortingSystem.h"
#include <iostream>

SortingSystem::SortingSystem() : token_cam(0) {}

void SortingSystem::pickUpToken() {
  transmitChar('p');
  waitForChar('p');//receiveChar();
  std::cout << "done waiting" << std::endl;
}

Color SortingSystem::checkTokenColor() { //this only reads once. We need to check the accuracy of the color detection.
                                         //if it's not consistently accurate we may need to read multiple times and get the most likely value.
  std::cout << "running check token color" << std::endl;
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
  
  switch(tokenColor) {
    case Color::GRAY : std::cout << "Gray Token Detected" << std::endl; break;
    case Color::RED : std::cout << "Red Token Detected" << std::endl; break;
    case Color::MAGENTA : std::cout << "Magenta Token Detected" << std::endl;
    case Color::CYAN : std::cout << "Cyan Token Detected" << std::endl; break;
    case Color::GREEN : std::cout << "Green Token Detected" << std::endl; break;
    case Color::BLUE : std::cout << "Blue Token Detected" << std::endl; break;
    default : std::cout << "Color not recognized" << std::endl; break;
  }
  return tokenColor;
}

void SortingSystem::storeToken(Color c) const {
  std::cout << "storing token" << std::endl;
  transmitChar('r');
  transmitColor(c);
}

void SortingSystem::sortToken() {
  std::cout << "picking up token my man" << std::endl;
  pickUpToken();
  storeToken(checkTokenColor());
  std::cout << std::endl;
}

void SortingSystem::dropTokenStack(Color c) {}
