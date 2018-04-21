#include "../include/Drivetrain.h"
#include <chrono>
#include <thread>

#include <iostream>

Drivetrain::Drivetrain() : nudge_speed(60) {}

void Drivetrain::stop() const {
  transmitChar(' ');
}

void Drivetrain::move(VelocityVector v) const {
  transmitChar('m');
  transmitVelocityVector(v);
}

void Drivetrain::nudge(VelocityVector v, double dist) {
  //std::cout << "nudging" << std::endl << std::endl;
  transmitChar('k');
  transmitBool(true);
  transmitChar('n');
  transmitVelocityVector(nudge_speed * v / v.magnitude);
  transmitValue(dist);
  waitForChar('+');
  //std::cout << "done nudging" << std::endl << std::endl;
}

void Drivetrain::travel(VelocityVector v, double dist, bool stopping) {
  std::cout << "travelling" << std::endl << std::endl;
  transmitChar('k');
  transmitBool(stopping);
  transmitChar('t');
  transmitVelocityVector(v);
  transmitValue(dist);
  waitForChar('+');
  std::cout << "done travelling" << std::endl << std::endl;
}
