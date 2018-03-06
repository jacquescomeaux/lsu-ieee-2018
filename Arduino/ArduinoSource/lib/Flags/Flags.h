#ifndef FLAG_H
#define FLAG_H

enum class Flag {
  NONE = static_cast<uint8_t>(0x00),
  FOLLOWING_LINE = static_cast<uint8_t>(0x01 << 0),
  CALIBRATING_LINE = static_cast<uint8_t>(0x01 << 1),
  PRINTING_LINE = static_cast<uint8_t>(0x01 << 2), //Serial Output
  PRINTING_EDGE = static_cast<uint8_t>(0x01 << 3),
  TRAVEL_TO_DST = static_cast<uint8_t>(0x01 << 4) //for Robot.moveSetDistance,
};

#endif//FLAG_H
