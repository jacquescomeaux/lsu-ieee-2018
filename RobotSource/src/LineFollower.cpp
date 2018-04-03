#include "../include/LineFollower.h"
#include <chrono>
#include <thread>

LineFollower::LineFollower() {}

void LineFollower::followLine(Direction dir) const {
  transmitChar('.');
  transmitIndex(2);
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
    case Direction::CLOCKWISE : transmitChar('s'); break;
    case Direction::COUNTER_CLOCKWISE : transmitChar('s'); break;
    default: transmitChar('s');
  }*/
  transmitChar('f');
}

void LineFollower::snapToLine(Direction dir, int range) const {
  followLine(dir);
  transmitChar('.');
  transmitIndex(range);
  transmitChar(' ');
  transmitChar('f');
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

void LineFollower::toggleCalibration() const {
  transmitChar('c');
}

void LineFollower::startCentering(bool cross, int offset) const {
  transmitChar('/');
  transmitIndex(offset);
  char centerChar = cross ? '|' : '\\';
  transmitChar(centerChar);
  /*std::this_thread::sleep_for(std::chrono::seconds(6)); //prev 6 secs
  transmitChar(centerChar);
  transmitChar(' ');
*/}


/*bool LineFollower::atIntersection() const {
  static char last_char = 'y';
  transmitChar('?');
  char current_char = receiveChar();
  bool atInt = (current_char == 'y' && last_char == 'n');
  last_char = current_char;
  return atInt;
}*/
