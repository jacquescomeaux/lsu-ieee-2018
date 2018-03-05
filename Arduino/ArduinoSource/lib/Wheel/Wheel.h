#ifndef WHEEL_H
#define WHEEL_H

#include <Adafruit_MotorShield.h>
#include <Encoder.h>

class Wheel {
  private:
    Adafruit_DCMotor* motor;
    Encoder encoder;
    Fixed speed, goal_speed;
    bool direction_set;
    const Fixed tolerance, max_speed, min_speed;
  public:
    Wheel(Adafruit_DCMotor*); 
    void setSpeed(Fixed);
    Fixed getSpeed() const;
    void adjustSpeed(Fixed);
    void approachSpeed(Fixed);
    void stop();
};

#endif//WHEEL_H
