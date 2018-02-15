#ifndef WHEEL_H
#define WHEEL_H

#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"

class Wheel {
  private:
    Adafruit_DCMotor* motor;
    int speed, desired_speed;
  public:
    Wheel(Adafruit_DCMotor*); 
    void setSpeed(int);
    void adjustSpeed(int);
    void approachSpeed();
    void stop();
};

#endif
