#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "Direction.h"

#include "SerialLink.h"

class LineFollower : private SerialLink {
  protected:
    LineFollower();
  public:
    void followLine(Direction, int, int) const;
    void followLine(Direction) const;
    void followLine(Direction, int) const;
    void toggleCalibration() const;
    void snapToLine(Direction, int) const;
    void startCentering(bool cross, int) const;
};

#endif//LINEFOLLOWER_H
