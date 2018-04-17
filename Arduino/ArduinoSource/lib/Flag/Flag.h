#ifndef FLAG_H
#define FLAG_H

enum class Flag : uint16_t {
  NONE = 0x00,
  FOLLOWING_LINE   = 0x0001 <<  0,
  CALIBRATING_LINE = 0x0001 <<  1,
  PRINTING_LINE    = 0x0001 <<  2,
  PRINTING_EDGE    = 0x0001 <<  3,
  TRAVELLING       = 0x0001 <<  4,
  STOPPING_INT     = 0x0001 <<  5,
  CENTERING_CROSS  = 0x0001 <<  6,
  CENTERING_CORNER = 0x0001 <<  7,
  AT_INTERSECTION  = 0x0001 <<  8,
  ON_LINE          = 0x0001 <<  9,
  STOP_AFTER_TRAVEL= 0x0001 << 10,
  CENTERING        = 0x0001 << 11
};

inline bool operator==(Flag a, Flag b) {return static_cast<uint16_t>(a) == static_cast<uint16_t>(b);}
inline bool operator!=(Flag a, Flag b) {return static_cast<uint16_t>(a) != static_cast<uint16_t>(b);}
inline Flag operator~(Flag a) {return static_cast<Flag>(~ static_cast<uint16_t>(a));}
inline Flag operator|(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));}
inline Flag operator&(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));}
inline Flag operator^(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint16_t>(a) ^ static_cast<uint16_t>(b));}
inline Flag operator|=(Flag& a, Flag b) {
  Flag A = static_cast<Flag>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
  a = A; 
  return a;
}
inline Flag operator&=(Flag& a, Flag b) {
  Flag A = static_cast<Flag>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
  a = A; 
  return a;
}
inline Flag operator^=(Flag& a, Flag b) {
  Flag A = static_cast<Flag>(static_cast<uint16_t>(a) ^ static_cast<uint16_t>(b));
  a = A; 
  return a;
}

#endif//FLAG_H
