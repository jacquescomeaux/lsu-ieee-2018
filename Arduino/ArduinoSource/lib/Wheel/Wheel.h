#ifndef WHEEL_H
#define WHEEL_H

#include <Adafruit_MotorShield.h>

class Wheel {
  private:
    const Adafruit_DCMotor* motor;
    int speed, desired_speed, corrected_speed;
    bool direction_set;
  public:
    Wheel(Adafruit_DCMotor*); 
    void setSpeed(int);
    int getSpeed() const;
    void adjustSpeed(int);
    void approachSpeed();
    void stop();
};

#endif//WHEEL_H
