#include "../include/LineFollower.h"
#include <chrono>
#include <thread>
#include <iostream>

LineFollower::LineFollower() {}

void LineFollower::followLine(Direction dir, int speed, int range) const {
  transmitChar('.');
  transmitIndex(range);
  transmitChar('M');
  transmitDirection(dir);
  transmitValue(speed);
  transmitChar('f');
}

void LineFollower::followLine(Direction dir) const {
  transmitChar('.');
  transmitIndex(2);
  transmitChar('m');
  transmitDirection(dir);
  transmitChar('f');
}

void LineFollower::followLine(Direction dir, int speed) const {
  transmitChar('.');
  transmitIndex(2);
  transmitChar('M');
  transmitDirection(dir);
  transmitValue(speed);
  transmitChar('f');
}

void LineFollower::snapToLine(Direction dir, int range) const {
  std::cout << "Snapping to line" << std::endl;
  followLine(dir);
  transmitChar('.');
  transmitIndex(range);
  transmitChar(' ');
  transmitChar('f');
  std::this_thread::sleep_for(std::chrono::seconds(2));
  transmitChar(' ');
  std::cout << "Done snapping to line" << std::endl << std::endl;
}

void LineFollower::toggleCalibration() const {
  transmitChar('c');
}

void LineFollower::startCentering(bool cross, int offset) const {
  transmitChar('/');
  transmitIndex(offset);
  char centerChar = cross ? '|' : '\\';
  transmitChar(centerChar);
  
/*  std::this_thread::sleep_for(std::chrono::seconds(6)); //prev 6 secs
  transmitChar(centerChar);
  transmitChar(' ');
*/}


/*bool LineFollower::atIntersection() const {
  static char last_char = 'y';
  transmitChar('?');
  char current_char = receiveChar();
  bool atInt = (current_char == 'y' && last_char == 'n');
  last_char = current_char;
  return atInt;
}*/
