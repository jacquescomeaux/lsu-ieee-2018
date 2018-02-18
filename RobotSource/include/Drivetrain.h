#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Wheel.h"
#include "SerialLink.h"
#include "Direction.h"

class Drivetrain : private SerialLink {
  private:
    const Wheel wheels[4];
  protected:
    Drivetrain();
  public:
    void move(Direction) const;
    void stop() const;
};

#endif
