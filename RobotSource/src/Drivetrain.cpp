#include "../include/Drivetrain.h"
#include <chrono>
#include <thread>

#include <iostream>

Drivetrain::Drivetrain() {}

void Drivetrain::stop() const {
  transmitChar(' ');
}

void Drivetrain::move(Direction dir) const {
  transmitChar('m');
  transmitDirection(dir);
}

void Drivetrain::setSpeed(int speed) const {
  transmitChar(',');
  transmitValue(speed);
}

void Drivetrain::move(Direction dir, int speed) const {
  transmitChar('M');
  transmitDirection(dir);
  transmitValue(speed);
}

void Drivetrain::nudge(Direction dir, double dist) {
  std::cout << "nudging robot in direction " << static_cast<int>(dir) << " by " << dist << " inches" <<  std::endl;
  transmitChar('k');
  transmitBool(true);
  transmitChar('n');
  transmitDirection(dir);
  transmitValue(dist);
  waitForChar('+');//receiveChar();
  std::cout << "done nudging" << std::endl << std::endl;
}

void Drivetrain::travel(Direction dir, int speed, double dist, bool stopping) {
//  std::cout << "travelling in direction " << static_cast<int>(dir) << " for " << dist << " inches at speed " << speed << std::endl;
  transmitChar('k');
  transmitBool(stopping);
  transmitChar('t');
  transmitDirection(dir);
  transmitValue(speed);
  transmitValue(dist);
  waitForChar('+');//receiveChar();
  //if(stopping) stop();
  std::cout << "done travelling" << std::endl << std::endl;
}

void Drivetrain::travel(double x, double y, double rot, double dist) {
  transmitChar('k');
  transmitBool(true);
  transmitChar('T');
  transmitValue(x);
  transmitValue(y);
  transmitValue(rot);
  transmitValue(dist);
  waitForChar('+');//receiveChar();
  //stop();
}
