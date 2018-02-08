#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include "SerialLink.h"

class LineFollower : private SerialLink {
  protected:
    LineFollower();
  public:
    void followUntilIntersection();
};

#endif
