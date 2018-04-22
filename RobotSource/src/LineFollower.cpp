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
  std::cout << "Sending follow line command" << std::endl;
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
