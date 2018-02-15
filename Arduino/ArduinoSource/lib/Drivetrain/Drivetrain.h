#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Wheel.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include <Direction.h>

class Drivetrain {
  private:
    Adafruit_MotorShield AFMS[2];
  protected:
    Drivetrain();
    Wheel wheels[4];
  public:
    void move(DIRECTION);
    void stop();
};

#endif
