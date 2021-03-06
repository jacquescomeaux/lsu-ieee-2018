#include "../include/VelocityVector.h"

#include <math.h>

VelocityVector::VelocityVector(double x_speed, double y_speed, double rot_speed) :
  RAD_TO_OFFSET(static_cast<double>(16) / 3.141592653589793),
  x(x_speed),
  y(y_speed),
  angle(computeAngle(x, y)),
  magnitude(computeMagnitude(x, y)),
  rot(rot_speed),
  offset(computeOffset(angle)) {}

double VelocityVector::computeAngle(double x_speed, double y_speed) const {
  double a = atan2(y_speed, x_speed);
  return a;
}

double VelocityVector::computeMagnitude(double x_speed, double y_speed) const {
  double m = sqrt((x_speed * x_speed) + (y_speed * y_speed));
  return m;
}

unsigned int VelocityVector::computeOffset(double a) const {
  int offset = static_cast<int>(a * RAD_TO_OFFSET);
  return static_cast<unsigned int>((offset + 32) % 32);
}
