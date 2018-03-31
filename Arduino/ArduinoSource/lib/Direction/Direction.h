#ifndef DIRECTION_H
#define DIRECTION_H

#include <ArduinoSTL.h>
#include <stdint.h>

enum class Direction : uint8_t {
  NONE = 0,
  FRONT = 1,
  BACK = 2,
  LEFT = 3,
  RIGHT = 4,
  FRONT_LEFT = 5,
  FRONT_RIGHT = 6,
  BACK_LEFT = 7,
  BACK_RIGHT = 8,
  CLOCKWISE = 9,
  COUNTER_CLOCKWISE = 10
};

#endif//DIRECTION_H
