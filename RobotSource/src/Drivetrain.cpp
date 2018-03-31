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

void Drivetrain::move(Direction dir, int speed) const {
  transmitChar('M');
  transmitDirection(dir);
  transmitValue(speed);
}

void Drivetrain::travel(Direction dir, int speed, float dist) const {
  transmitChar('t');
  transmitDirection(dir);
  transmitValue(speed);
  transmitValue(dist);
  receiveChar();
}
