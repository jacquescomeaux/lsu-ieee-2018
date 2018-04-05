#include "../include/SortingSystem.h"
#include <iostream>

SortingSystem::SortingSystem() :
  COLOR_POSITIONS {0, 4, 3, 2, 5, 6, 7, 1},
  token_cam(0),
  held_token(NULL),
  plate_position(0) {}

bool SortingSystem::pickUpToken() {
  transmitChar('p');
  waitForChar('p');
  std::cout << "done waiting" << std::endl;
  Color seen = token_cam.getTokenColor();
  if(seen == Color::NONE || seen == Color::WHITE || seen == Color::BLACK) return false;
  held_token = new Token(seen);
  return true;
}

void SortingSystem::storeToken(Token* t) {
  std::cout << "storing token" << std::endl;
  transmitChar('r');
  //waitForChar('r');
  transmitColor(t->getColor());
  token_stacks[COLOR_POSITIONS[static_cast<int>(t->getColor())] - 1].push_back(t);
}

void SortingSystem::sortToken() {
  std::cout << "picking up token my man" << std::endl;
  if(pickUpToken()) {
    storeToken(held_token);
    held_token = NULL;
  }
  std::cout << std::endl;
}

bool SortingSystem::dropTokenStack(Color c) {
  int next_pos = plate_position + 7;
  next_pos %= 8;
  if(next_pos != COLOR_POSITIONS[static_cast<int>(c)]) return false;
  transmitChar('d');
  plate_position = next_pos;
  return true;
}
