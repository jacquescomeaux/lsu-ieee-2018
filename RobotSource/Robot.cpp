#include "Robot.h"
#include "Coord.h"

#include <cmath>
#include <iostream>

Robot::Robot() {
  RS232_OpenComport(PORTNUM, 9600, "8N1");
}

Robot::Robot(Coord l) : location(l), heading(90), totaldist(0), totalrot(0), totalvert(0), record(false) {}

StoreBot::StoreBot() {}

StoreBot::StoreBot(Coord l) : Robot(l), totalside(0) {}

SortBot::SortBot() {}

SortBot::SortBot(Coord l) : Robot(l), totalplate(0), topplate(0), botplate(0) {}

Coord Robot::getLocation() const {
  return location;
}

double Robot::getHeading() const {
  return heading;
}

/*void Robot::moveToLocation(Coord l) {
  if(record) std::cout << "1 " << location.dist(l) << " " << (180 * std::atan2(l.y-location.y, l.x-location.x) / M_PI) - heading << std::endl;
  totaldist += location.dist(l);
  setLocation(l);
}*/

void Robot::rotateToAngle(double a) {
  if(record) std::cout << "2 " << a - heading << std::endl;
  totalrot += std::abs(heading - a);
  setHeading(a);
}

void Robot::moveToNearestToken(Board* b) {
  Coord min(2*b->getWidth(), 2*b->getLength());
  for(int i = 0; i < b->tokens.size(); i++) {
    Token* t = &b->tokens[i];
    color_opt c =t->getColor();
    Coord l = t->getLocation();
    bool correct = ((std::abs(l.x-SQUARES[c].x) < 0.5) && (std::abs(l.y-SQUARES[c].y) < 0.5));
    if(!correct && !t->onBot) if(location.dist(l) < location.dist(min)) min = l;
  }
  moveToLocation(min);
}

void Robot::pickUpToken(Board* b) {
  for(int i = 0; i < b->tokens.size(); i++) if(location.dist(b->tokens[i].getLocation()) <= GRAB_DIST) {
    if(record) std::cout << "3 " << -1 * VERT_DIST << std::endl;
    if(record) std::cout << "3 " << VERT_DIST << std::endl;
    held = &b->tokens[i];
    held->onBot = true;
    totalvert += 2 * VERT_DIST;
    break;
  }
}

color_opt Robot::checkTokenColor() const {
  if(held != NULL) return held->getColor();
  else return GRAY;
}

void Robot::dropToken() {
  if(held != NULL) {
    if(record) std::cout << "3 " << -1 * VERT_DIST << std::endl;
    if(record) std::cout << "3 " << VERT_DIST << std::endl;
    held->setLocation(location); //+random coord;
    held->onBot = false;
    held = NULL;
    totalvert += 2 * VERT_DIST;
  }
}

void Robot::printDists() const {
  std::cout << "Total distance travelled: " << totaldist << std::endl;
  std::cout << "Total robot rotation: " << totalrot << " degrees" << std::endl;
  std::cout << "Total vertical arm distance: " << totalvert << std::endl;
}

double Robot::getDist() const {
  return totaldist;
}

double Robot::getRot() const {
  return totalrot;
}

double Robot::getVert() const {
  return totalvert;
}

void Robot::recordMoves(bool b) {
  record = b;
}

void SortBot::sortToken() {
  if(held != NULL) placeTokenInStack(checkTokenColor());
}

void SortBot::placeTokenInStack(color_opt c) {
  rotatePlates(STACK_POS[c]);
  stacks[c].push_back(held);
  held = NULL;
  rotatePlates(0);
}

void SortBot::dropStack(color_opt c) {
  rotateTop(STACK_POS[c]);//drop those in between
  for(int i = 0; i < stacks[c].size(); i++) {
    stacks[c][i]->setLocation(getLocation()); //+random coord
    stacks[c][i]->onBot = false;
  }
  stacks[c].clear();
}

void SortBot::rotatePlates(int pos) { 
  if(record) std::cout << "5 " << 45 * ((8+pos-topplate)%8) << std::endl;
  totalplate += (8 + pos - topplate) % 8;
  topplate = pos;
  botplate = pos;
}

void SortBot::rotateTop(int pos) {
  if(record) std::cout << "5 " << -1 * 45 * ((8+topplate-pos)%8) << std::endl;
  totalplate += (8 + topplate - pos) % 8;
  topplate = pos;
}

void SortBot::printDists() const {
  Robot::printDists();
  std::cout << "Total plate rotation: " << 45*totalplate << " degrees" << std::endl;
}

double SortBot::getPlate() const {
  return totalplate;
}
