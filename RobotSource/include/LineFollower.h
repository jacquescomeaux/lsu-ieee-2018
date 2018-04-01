#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "Direction.h"

#include "SerialLink.h"

class LineFollower : private SerialLink {
  protected:
    LineFollower();
  public:
    void followLine(Direction) const;
    void toggleCalibration() const;
    void snapToLine(Direction) const;
    void center(bool cross, int) const;
};

#endif//LINEFOLLOWER_H
