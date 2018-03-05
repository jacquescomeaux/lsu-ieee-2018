#ifndef FIXED_H
#define FIXED_H

#include <cstdint>
#include <cstddef>

class Fixed {
  private:
    static const size_t shift;
    static const uint64_t factor;
    int64_t internal;
  public:
    Fixed();
    Fixed(int32_t);
    Fixed(double);
    Fixed& operator=(int32_t);
    Fixed& operator=(double);
    Fixed& operator+=(const Fixed&);
    Fixed& operator+=(int32_t);
    Fixed& operator-=(const Fixed&);
    Fixed& operator-=(int32_t);
    Fixed& operator*=(const Fixed&);
    Fixed& operator*=(int32_t);
    Fixed& operator/=(const Fixed&);
    Fixed& operator/=(int32_t);
    Fixed abs() const;
    int64_t getInternal() const;
    double getDouble() const;
};

inline bool operator==(const Fixed&, const Fixed&);
inline bool operator!=(const Fixed&, const Fixed&);
inline bool operator< (const Fixed&, const Fixed&);
inline bool operator> (const Fixed&, const Fixed&);
inline bool operator<=(const Fixed&, const Fixed&);
inline bool operator>=(const Fixed&, const Fixed&);
inline Fixed operator+(Fixed, const Fixed&);
inline Fixed operator+(Fixed, int32_t);
inline Fixed operator+(int32_t, Fixed);
inline Fixed operator-(Fixed, const Fixed&);
inline Fixed operator-(Fixed, int32_t);
inline Fixed operator-(int32_t, Fixed);
inline Fixed operator*(Fixed, Fixed);
inline Fixed operator*(Fixed, int32_t);
inline Fixed operator*(int32_t, Fixed);
inline Fixed operator/(Fixed, const Fixed&);
inline Fixed operator/(Fixed, int32_t);
inline Fixed operator/(int32_t, Fixed);

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

inline Fixed operator+(Fixed lhs, int32_t rhs) {
  lhs += rhs;
  return lhs;
}

inline Fixed operator+(int32_t lhs, Fixed rhs) {
  rhs += lhs;
  return lhs;
}

inline Fixed operator-(Fixed lhs, const Fixed& rhs) {
  lhs -= rhs;
  return lhs;
}

inline Fixed operator-(Fixed lhs, int32_t rhs) {
  lhs -= rhs;
  return lhs;
}

inline Fixed operator-(int32_t lhs, Fixed rhs) {
  rhs -= lhs;
  return lhs;
}

inline Fixed operator*(Fixed lhs, Fixed rhs) {
  lhs *= rhs;
  return lhs;
}

inline Fixed operator*(Fixed lhs, int32_t rhs) {
  lhs *= rhs;
  return lhs;
}

inline Fixed operator*(int32_t lhs, Fixed rhs) {
  rhs *= lhs;
  return lhs;
}

inline Fixed operator/(Fixed lhs, const Fixed& rhs) {
  lhs /= rhs;
  return lhs;
}

inline Fixed operator/(Fixed lhs, int32_t rhs) {
  lhs /= rhs;
  return lhs;
}

inline Fixed operator/(int32_t lhs, Fixed rhs) {
  Fixed result = lhs;
  result /= rhs;
  return result;
}

#endif//FIXED_H
