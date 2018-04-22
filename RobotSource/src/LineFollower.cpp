#include "../include/LineFollower.h"
#include <chrono>
#include <thread>
#include <iostream>

LineFollower::LineFollower() {}

void LineFollower::followLine(VelocityVector v, int range) {
  std::cout << "Following line" << std::endl;
  transmitChar('/');
  transmitIndex(v.offset);
  transmitChar('.');
  transmitIndex(range);
  transmitChar('m');
  std::cout << "x" << v.x << "y" << v.y << "rot" << v.rot << "mag" << v.magnitude << "angle" << v.angle << "offset" << v.offset << std::endl;
  transmitVelocityVector(v);
  transmitChar('f');
  waitForChar('f');
}

void LineFollower::align(VelocityVector v, int range) {
  std::cout << "Snapping to line" << std::endl;
  transmitChar('/');
  transmitIndex(v.offset);
  transmitChar('.');
  transmitIndex(range);
  //followLine(v, range);
  transmitChar(' ');
  transmitChar('f');
  std::this_thread::sleep_for(std::chrono::seconds(1));
  transmitChar(' ');
  std::cout << "Done snapping to line" << std::endl << std::endl;
  waitForChar('f');
  waitForChar(' ');
  waitForChar(' ');
}

void LineFollower::toggleCalibration() {
  transmitChar('c');
  waitForChar('c');
}
