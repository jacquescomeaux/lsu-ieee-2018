#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "SerialLink.h"

class LineFollower : private SerialLink {
  protected:
    LineFollower();
  public:
    void followLine(VelocityVector, int) const;
    void toggleCalibration() const;
    void align(VelocityVector, int) const;
};

#endif//LINEFOLLOWER_H
