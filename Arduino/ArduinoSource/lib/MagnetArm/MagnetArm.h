#ifndef MAGNETARM_H
#define MAGNETARM_H

#include <Adafruit_MotorShield.h>

class MagnetArm {
  private:
    const uint16_t RPM;
    const int bot_target, top_target, cam_target, total_steps;
    int position, target_position;
    Adafruit_StepperMotor* motor;
    Adafruit_DCMotor* magnet;
    void goToHeight(int);
    void magnetize();
    void demagnetize();
  public:
    MagnetArm(Adafruit_StepperMotor* , Adafruit_DCMotor*);
    void reset();
    void pickUpToken();
    void storeToken();
    //void goToTop();
};

#endif//MAGNETARM_H
