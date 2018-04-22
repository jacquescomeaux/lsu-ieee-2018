#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "SerialLink.h"

class LineFollower : private SerialLink {
  protected:
    LineFollower();
  public:
    void followLine(VelocityVector, int);
    void toggleCalibration();
    void align(VelocityVector, int);
};

#endif//LINEFOLLOWER_H
