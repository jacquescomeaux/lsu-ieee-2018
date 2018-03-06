#ifndef MOTORSHIELD_H
#define MOTORSHIELD_H

#include <Adafruit_MotorShield.h>

class MotorShield {
  private:
    Adafruit_MotorShield AFMS;
  public:
    MotorShield();
    MotorShield(uint8_t);
    MotorShield(uint8_t, uint16_t);
    Adafruit_DCMotor* getMotor(uint8_t) ;//const; 
};

#endif//MOTORSHIELD_H
