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
  /*switch(dir) {
    case Direction::NONE : transmitChar('s'); break;
    case Direction::FRONT : transmitChar('w'); break;
    case Direction::BACK : transmitChar('x'); break;
    case Direction::LEFT : transmitChar('a'); break;
    case Direction::RIGHT : transmitChar('d'); break;
    case Direction::FRONT_LEFT : transmitChar('q'); break;
    case Direction::FRONT_RIGHT : transmitChar('e'); break;
    case Direction::BACK_LEFT : transmitChar('z'); break;
    case Direction::BACK_RIGHT : transmitChar('c'); break;
    case Direction::CLOCKWISE : transmitChar('j'); break;
    case Direction::COUNTER_CLOCKWISE : transmitChar('k'); break;
    default: transmitChar('s');
  }*/
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

void Drivetrain::nudge(Direction dir, float dist) {
  std::cout << "nudging robot in direction " << static_cast<int>(dir) << " by " << dist << " inches" <<  std::endl;
  transmitChar('k');
  transmitBool(true);
  transmitChar('n');
  transmitDirection(dir);
  transmitValue(dist);
  waitForChar('+');//receiveChar();
  std::cout << "done nudging" << std::endl << std::endl;
}

void Drivetrain::travel(Direction dir, int speed, float dist, bool stopping) {
  std::cout << "travelling in direction " << static_cast<uint8_t>(dir) << " for " << dist << " inches at speed " << speed << std::endl;
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

void Drivetrain::travel(float x, float y, float rot, float dist) {
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
