#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

class LineFollower : private SerialLink {
  public:
    LineFollower();
    void followUntilIntersection();
};

#endif
