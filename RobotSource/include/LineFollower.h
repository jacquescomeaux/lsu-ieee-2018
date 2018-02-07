#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

class LineFollower : private SerialLink {
  protected:
    LineFollower();
  public:
    void followUntilIntersection();
};

#endif
