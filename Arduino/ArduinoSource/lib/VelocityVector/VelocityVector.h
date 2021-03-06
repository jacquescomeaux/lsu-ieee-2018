#ifndef VELOCITYVECTOR_H
#define VELOCITYVECTOR_H

#include <Fixed.h>

class VelocityVector {
  private:
    const Fixed RAD_TO_OFFSET;
    Fixed computeAngle(Fixed, Fixed) const;
    Fixed computeMagnitude(Fixed, Fixed) const;
    unsigned int computeOffset(Fixed) const;
  public:
    const Fixed x, y, angle, magnitude, rot;
    const unsigned int offset;
    VelocityVector(Fixed x, Fixed y, Fixed rot);
};

#endif//VELOCITYVECTOR_H
