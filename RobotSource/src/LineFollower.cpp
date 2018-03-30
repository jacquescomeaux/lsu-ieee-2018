#include "../include/LineFollower.h"

LineFollower::LineFollower() {}

void LineFollower::followLine(Direction dir) const {
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
    case Direction::CLOCKWISE : transmitChar('s'); break;
    case Direction::COUNTER_CLOCKWISE : transmitChar('s'); break;
    default: transmitChar('s');
  }
  transmitChar('f');
}

void LineFollower::snapToLine(Direction dir) const {
  followLine(dir);
  transmitChar('s');
}

bool LineFollower::atIntersection() const {
  static char last_char = 'y';
  transmitChar('?');
  char current_char = receiveChar();
  bool atInt = (current_char == 'y' && last_char == 'n');
  last_char = current_char;
  return atInt;
}
