#include "../include/Drivetrain.h"
#include <chrono>
#include <thread>

#include <iostream>

Drivetrain::Drivetrain() : nudge_speed(60) {}

void Drivetrain::stop() {
  transmitChar(' ');
  waitForChar(' ');
}

void Drivetrain::move(VelocityVector v) {
  transmitChar('m');
  transmitVelocityVector(v);
  waitForChar('m');
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
  std::cout << "x" << v.x << "y" << v.y << "rot" << v.rot << "mag" << v.magnitude << "angle" << v.angle << "offset" << v.offset << std::endl;
  std::cout << "DIST " << dist << std::endl;
  transmitChar('k');
  transmitBool(stopping);
  transmitChar('t');
  transmitVelocityVector(v);
  transmitValue(dist);
  waitForChar('+');
  std::cout << "done travelling" << std::endl << std::endl;
}
