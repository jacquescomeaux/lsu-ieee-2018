#ifndef FLAG_H
#define FLAG_H

enum class Flag : uint8_t {
  NONE = 0x00,
  FOLLOWING_LINE   = 0x01 << 0,
  CALIBRATING_LINE = 0x01 << 1,
  PRINTING_LINE    = 0x01 << 2,
  PRINTING_EDGE    = 0x01 << 3,
  TRAVEL_TO_DST    = 0x01 << 4
};

inline bool operator==(Flag a, Flag b) {return static_cast<uint8_t>(a) == static_cast<uint8_t>(b);}
inline bool operator!=(Flag a, Flag b) {return static_cast<uint8_t>(a) != static_cast<uint8_t>(b);}
inline Flag operator~(Flag a) {return static_cast<Flag>(~ static_cast<uint8_t>(a));}
inline Flag operator|(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));}
inline Flag operator&(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));}
inline Flag operator^(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));}
inline Flag operator|=(Flag& a, Flag b) {
  Flag A = static_cast<Flag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
  a = A; 
  return a;
}
inline Flag operator&=(Flag& a, Flag b) {
  Flag A = static_cast<Flag>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
  a = A; 
  return a;
}
inline Flag operator^=(Flag& a, Flag b) {
  Flag A = static_cast<Flag>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
  a = A; 
  return a;
}

#endif//FLAG_H
