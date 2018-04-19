#include "../include/LineFollower.h"
#include <chrono>
#include <thread>
#include <iostream>

LineFollower::LineFollower() {}

void LineFollower::followLine(VelocityVector v, int range) const {
  transmitChar('/');
  transmitIndex(v.offset);
  transmitChar('.');
  transmitIndex(range);
  transmitChar('m');
  transmitVelocityVector(v);
  transmitChar('f');
}

void LineFollower::align(VelocityVector v, int range) const {
  std::cout << "Snapping to line" << std::endl;
  followLine(v, range);
  transmitChar(' ');
  transmitChar('f');
  std::this_thread::sleep_for(std::chrono::seconds(2));
  transmitChar(' ');
  std::cout << "Done snapping to line" << std::endl << std::endl;
}

void LineFollower::toggleCalibration() const {
  transmitChar('c');
}

/*void LineFollower::startCentering(bool cross, int offset) const {
  transmitChar('/');
  transmitIndex(offset);
  char centerChar = cross ? '|' : '\\';
  transmitChar(centerChar);
  
  //std::this_thread::sleep_for(std::chrono::seconds(6)); //prev 6 secs
  //transmitChar(centerChar);
  //transmitChar(' ');
}
*/

void LineFollower::center() const {
  transmitChar('|');
  std::this_thread::sleep_for(std::chrono::seconds(6)); //prev 6 secs
  transmitChar('|');
  transmitChar(' ');
}
