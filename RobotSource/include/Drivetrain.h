#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Direction.h"

#include "SerialLink.h"

class Drivetrain : private SerialLink {
  protected:
    Drivetrain();
  public:
    void stop() const;
    void setSpeed(int) const;
    void move(Direction) const;
    void move(Direction, int) const;
    void nudge(Direction, float);
    void travel(Direction, int, float, bool);
    void travel(float, float, float, float);
};

#endif//DRIVETRAIN_H
