#ifndef FLAG_H
#define FLAG_H

enum class Flag : uint8_t {
  /*NONE = static_cast<uint8_t>(0x00),
  FOLLOWING_LINE = static_cast<uint8_t>(0x01 << 0),
  CALIBRATING_LINE = static_cast<uint8_t>(0x01 << 1),
  PRINTING_LINE = static_cast<uint8_t>(0x01 << 2),
  PRINTING_EDGE = static_cast<uint8_t>(0x01 << 3)
  */NONE = 0x00,
  FOLLOWING_LINE = 0x01 << 0,
  CALIBRATING_LINE = 0x01 << 1,
  PRINTING_LINE = 0x01 << 2,
  PRINTING_EDGE = 0x01 << 3,
  TRAVEL_TO_DST = 0x01 << 4
};

inline Flag operator~(Flag a) {return static_cast<Flag>(~ static_cast<uint8_t>(a));}
inline Flag operator|(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));}
inline Flag operator&(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));}
inline Flag operator^(Flag a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));}
inline Flag operator|=(Flag& a, Flag b) {
  uint8_t A = static_cast<uint8_t>(a);
  uint8_t B = static_cast<uint8_t>(b);
  A |= B;
  return static_cast<Flag>(A);
}
inline Flag operator&=(Flag& a, Flag b) {
  uint8_t A = static_cast<uint8_t>(a);
  uint8_t B = static_cast<uint8_t>(b);
  A &= B;
  return static_cast<Flag>(A);
}
inline Flag operator^=(Flag& a, Flag b) {
  uint8_t A = static_cast<uint8_t>(a);
  uint8_t B = static_cast<uint8_t>(b);
  A ^= B;
  return static_cast<Flag>(A);
}
//inline Flag& operator&=(Flag& a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) &= static_cast<uint8_t>(b));}
//inline Flag& operator^=(Flag& a, Flag b) {return static_cast<Flag>(static_cast<uint8_t>(a) ^= static_cast<uint8_t>(b));}

/*constexpr enum Flag operator |(const enum Flag selfValue, const enum Flag inValue ) {
  return (enum Flag)(uint8_t(selfValue) | uint8_t(inValue));
}
constexpr enum Flag operator &(const enum Flag selfValue, const enum Flag inValue ) {
  return (enum Flag)(uint8_t(selfValue) & uint8_t(inValue));
}
constexpr enum Flag operator ^(const enum Flag selfValue, const enum Flag inValue ) {
  return (enum Flag)(uint8_t(selfValue) ^ uint8_t(inValue));
}
constexpr enum Flag operator ~(const enum Flag inValue ) {
  return (enum Flag)(~uint8_t(inValue));
}
constexpr enum Flag& operator &=( const enum Flag& selfValue, const enum Flag inValue ) {
  return (enum Flag&)(uint8_t(selfValue) = uint8_t(selfValue) & uint8_t(inValue));
}
constexpr enum Flag& operator |=( const enum Flag& selfValue, const enum Flag inValue ) {
  return (enum Flag&)(uint8_t(selfValue) |= uint8_t(inValue));
}
constexpr enum Flag& operator ^=( const enum Flag& selfValue, const enum Flag inValue ) {
  return (enum Flag&)(uint8_t(selfValue) ^= uint8_t(inValue));
}*/



#endif//FLAG_H
