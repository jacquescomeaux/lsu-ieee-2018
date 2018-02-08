#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Wheel.h"
#include "SerialLink.h"

class Drivetrain : private SerialLink {
  private:
    Wheel wheels[4];
  protected:
    Drivetrain();
};

#endif
