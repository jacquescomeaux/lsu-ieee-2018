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
    void move(Direction) const;
    void stop() const;
    void center() const;
};

#endif//DRIVETRAIN_H
