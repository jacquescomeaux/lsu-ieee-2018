#ifndef WHEEL_H
#define WHEEL_H

#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class Wheel {
  private:
    int speed;
    Adafruit_DCMotor* motor;
  public:
    Wheel(Adafruit_DCMotor*); 
    void stop();
};

#endif
