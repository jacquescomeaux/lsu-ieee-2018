#ifndef WHEEL_H
#define WHEEL_H

class Wheel {
  private:
    Adafruit_MotorShield AFMS[2];
    Adafruit_DCMotor* motors[4];
  public:
    Wheel(); 
};

#endif
