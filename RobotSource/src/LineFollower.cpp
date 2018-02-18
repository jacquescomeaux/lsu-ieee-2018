#include "../include/LineFollower.h"

LineFollower::LineFollower() {}

void LineFollower::followLine(Direction dir) const {
  switch(dir) {
    case Direction::NONE : transmitChar('s'); break;
    case Direction::FRONT : transmitChar('W'); break;
    case Direction::BACK : transmitChar('X'); break;
    case Direction::LEFT : transmitChar('A'); break;
    case Direction::RIGHT : transmitChar('D'); break;
    case Direction::FRONT_LEFT : transmitChar('Q'); break;
    case Direction::FRONT_RIGHT : transmitChar('E'); break;
    case Direction::BACK_LEFT : transmitChar('Z'); break;
    case Direction::BACK_RIGHT : transmitChar('C'); break;
    case Direction::CLOCKWISE : transmitChar('s'); break;
    case Direction::COUNTER_CLOCKWISE : transmitChar('s'); break;
    default: transmitChar('s');
  }
}

