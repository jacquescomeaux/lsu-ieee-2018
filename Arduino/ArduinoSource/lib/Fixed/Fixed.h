#ifndef FIXED_H
#define FIXED_H

//#include <StandardCplusplus/stdint.h>///cstdint>
//#include <StandardCplusplus/cstddef>///cstdint>
#include <StandardCplusplus.h>
//#include <iostream>
#include <stdint.h>
#include <cstddef>
//#include <StandardCplusplus/cstddef>

class Fixed {
  private:
    static const size_t shift;
    static const uint64_t factor;
    int64_t internal;
  public:
    Fixed();
    Fixed(int);
    Fixed(double);
    Fixed& operator=(int);
    Fixed& operator=(double);
    Fixed& operator+=(const Fixed&);
    Fixed& operator+=(int);
    Fixed& operator-=(const Fixed&);
    Fixed& operator-=(int);
    Fixed& operator*=(const Fixed&);
    Fixed& operator*=(int);
    Fixed& operator/=(const Fixed&);
    Fixed& operator/=(int);
    Fixed mag() const;
    int64_t getInternal() const;
    double getDouble() const;
    int getInt() const;
};

inline bool operator==(const Fixed&, const Fixed&);
inline bool operator!=(const Fixed&, const Fixed&);
inline bool operator< (const Fixed&, const Fixed&);
inline bool operator> (const Fixed&, const Fixed&);
inline bool operator<=(const Fixed&, const Fixed&);
inline bool operator>=(const Fixed&, const Fixed&);
inline Fixed operator+(Fixed, const Fixed&);
inline Fixed operator+(Fixed, int);
inline Fixed operator+(int, Fixed);
inline Fixed operator-(Fixed, const Fixed&);
inline Fixed operator-(Fixed, int);
inline Fixed operator-(int, Fixed);
inline Fixed operator*(Fixed, Fixed);
inline Fixed operator*(Fixed, int);
inline Fixed operator*(int, Fixed);
inline Fixed operator/(Fixed, const Fixed&);
inline Fixed operator/(Fixed, int);
inline Fixed operator/(int, Fixed);

inline bool operator==(const Fixed& lhs, const Fixed& rhs) {
  return lhs.getInternal() == rhs.getInternal();
}

inline bool operator!=(const Fixed& lhs, const Fixed& rhs) {
  return !operator==(lhs,rhs);
}

inline bool operator< (const Fixed& lhs, const Fixed& rhs) {
  return (lhs.getInternal() - rhs.getInternal()) < 0;
}

inline bool operator> (const Fixed& lhs, const Fixed& rhs) {
  return  operator< (rhs,lhs);
}

inline bool operator<=(const Fixed& lhs, const Fixed& rhs) {
  return !operator> (lhs,rhs);
}

inline bool operator>=(const Fixed& lhs, const Fixed& rhs) {
  return !operator< (lhs,rhs);
} 

inline Fixed operator+(Fixed lhs, const Fixed& rhs) {
  lhs += rhs;
  return lhs;
}

inline Fixed operator+(Fixed lhs, int rhs) {
  lhs += rhs;
  return lhs;
}

inline Fixed operator+(int lhs, Fixed rhs) {
  rhs += lhs;
  return rhs;
}

inline Fixed operator-(Fixed lhs, const Fixed& rhs) {
  lhs -= rhs;
  return lhs;
}

inline Fixed operator-(Fixed lhs, int rhs) {
  lhs -= rhs;
  return lhs;
}

inline Fixed operator-(int lhs, Fixed rhs) {
  rhs -= lhs;
  return rhs;
}

inline Fixed operator*(Fixed lhs, Fixed rhs) {
  lhs *= rhs;
  return lhs;
}

inline Fixed operator*(Fixed lhs, int rhs) {
  lhs *= rhs;
  return lhs;
}

inline Fixed operator*(int lhs, Fixed rhs) {
  rhs *= lhs;
  return rhs;
}

inline Fixed operator/(Fixed lhs, const Fixed& rhs) {
  lhs /= rhs;
  return lhs;
}

inline Fixed operator/(Fixed lhs, int rhs) {
  lhs /= rhs;
  return lhs;
}

inline Fixed operator/(int lhs, Fixed rhs) {
  Fixed result = lhs;
  result /= rhs;
  return result;
}

#endif//FIXED_H
