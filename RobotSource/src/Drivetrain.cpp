#include "../include/Drivetrain.h"
#include <chrono>
#include <thread>

Drivetrain::Drivetrain() {}

void Drivetrain::move(Direction dir) const {
  switch(dir) {
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
  }
}

void Drivetrain::stop() const {
  transmitChar('s');
}

void Drivetrain::center() const {
  transmitChar('\\');
  std::this_thread::sleep_for(std::chrono::seconds(3));
  transmitChar('\\');
}
