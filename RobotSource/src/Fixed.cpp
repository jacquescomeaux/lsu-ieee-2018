#include "../include/Fixed.h"

const size_t Fixed::shift = 8 * sizeof(int32_t);
const uint64_t Fixed::factor = static_cast<uint64_t>(1) << shift; 

Fixed::Fixed() : Fixed(0) {}

Fixed::Fixed(int32_t i) : internal(static_cast<int64_t>(i) << shift) {}

Fixed::Fixed(uint64_t i) : internal(i) {}

Fixed::Fixed(double d) {
  internal = static_cast<int64_t>(d * static_cast<double>(factor));
}

Fixed& Fixed::operator=(int32_t i) {
  internal = static_cast<int64_t>(i) << shift;
  return *this;
}

Fixed& Fixed::operator=(double d) {
  internal = static_cast<int64_t>(d * static_cast<double>(factor));
  return *this;
}

Fixed& Fixed::operator+=(const Fixed& rhs) {
  internal += rhs.getInternal();
  return *this;
}

Fixed& Fixed::operator+=(int32_t rhs) {
  internal += static_cast<int64_t>(rhs) << shift;
  return *this;
}

Fixed& Fixed::operator-=(const Fixed& rhs) {
  internal -= rhs.getInternal();
  return *this;
}

Fixed& Fixed::operator-=(int32_t rhs) {
  internal -= static_cast<int64_t>(rhs) << shift;
  return *this;
}

Fixed& Fixed::operator*=(const Fixed& rhs) {
  internal = (internal >> (shift/2)) * (rhs.getInternal() >> (shift/2));
  return *this;
}

Fixed& Fixed::operator*=(int32_t rhs) {
  internal *= rhs;
  return *this;
}

Fixed& Fixed::operator/=(const Fixed& rhs) {
  internal = (internal / rhs.getInternal()) << shift;
  return *this;
}

Fixed& Fixed::operator/=(int32_t rhs) {
  internal /= static_cast<int64_t>(rhs) << shift;
  return *this;
}

Fixed Fixed::mag() const {
  if(*this < Fixed(0)) return Fixed(-1) * *this;
  return *this;
}

int64_t Fixed::getInternal() const {
  return internal;
}

int32_t Fixed::getInt() const {
  return static_cast<int32_t>(internal >> shift);
}

double Fixed::getDouble() const {
  return static_cast<double>(internal) / static_cast<double>(factor);
}
