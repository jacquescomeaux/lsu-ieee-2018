#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Direction.h"

#include "SerialLink.h"

#include "Wheel.h"

class Drivetrain : private SerialLink {
  private:
    const Wheel wheels[4];
  protected:
    Drivetrain();
  public:
    void stop() const;
    void setSpeed(int) const;
    void move(Direction) const;
    void move(Direction, int) const;
    void travel(Direction, int, float) const;
};

#endif//DRIVETRAIN_H
