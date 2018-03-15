#ifndef MAGNETARM_H
#define MAGNETARM_H

#include <Adafruit_MotorShield.h>

class MagnetArm {
  private:
    const uint16_t RPM;
    const int /*step_amount,*/ bot_target, /*mid_target,*/ top_target, total_steps;
    //bool moving;
    int position, target_position;
    Adafruit_StepperMotor* motor;
    void goToHeight(int);
    void magnetize() const;
    void demagnetize() const;
  public:
    MagnetArm(Adafruit_StepperMotor*);
    //void ready();
    void reset();
    void pickUpToken();
    void storeToken() const;
};

#endif//MAGNETARM_H
