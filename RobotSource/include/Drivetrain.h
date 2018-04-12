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
    void nudge(Direction, double);
    void travel(Direction, int, double, bool);
    void travel(double, double, double, double);
};

#endif//DRIVETRAIN_H
