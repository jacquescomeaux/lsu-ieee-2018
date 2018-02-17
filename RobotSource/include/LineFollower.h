#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "SerialLink.h"
#include "Direction.h"

class LineFollower : private SerialLink {
  protected:
    LineFollower();
  public:
    void followLine(Direction) const;
    void followUntilIntersection(Direction) const;
};

#endif
