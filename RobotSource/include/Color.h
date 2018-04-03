#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

enum class Color : uint8_t {
  NONE = 0,
  RED = 1,
  GREEN = 2,
  BLUE = 3,
  CYAN = 4,
  MAGENTA = 5,
  YELLOW = 6,
  GRAY = 7,
  WHITE = 8,
  BLACK = 9
};

#endif
