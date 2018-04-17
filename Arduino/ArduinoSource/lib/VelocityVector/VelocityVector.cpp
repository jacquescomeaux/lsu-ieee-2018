#include <VelocityVector.h>

#include <math.h>

VelocityVector::VelocityVector(Fixed x_speed, Fixed y_speed, Fixed rot_speed) :
  RAD_TO_OFFSET(static_cast<double>(16) / 3.141592653589793),
  x(x_speed),
  y(y_speed),
  rot(rot_speed),
  angle(computeAngle(x, y)),
  magnitude(computeMagnitude(x, y)),
  offset(computeOffset(angle)) {}

Fixed VelocityVector::computeAngle(Fixed x_speed, Fixed y_speed) const {
  Fixed a = atan2(y_speed.getDouble(), x_speed.getDouble());
  return a;
}

Fixed VelocityVector::computeMagnitude(Fixed x_speed, Fixed y_speed) const {
  Fixed m = sqrt(((x_speed * x_speed) + (y_speed * y_speed)).getDouble());
  return m;
}

unsigned int VelocityVector::computeOffset(Fixed a) const {
  return static_cast<unsigned int>((a * RAD_TO_OFFSET).getInt());
}
