#ifndef SORTINGPLATE_H
#define SORTINGPLATE_H

#include <Adafruit_MotorShield.h>

class SortingPlate {
  private:
    const uint16_t RPM;
    const unsigned int step_amount, target_step, total_steps;
    bool moving;
    unsigned int position, target_position, bottom_offset;
    Adafruit_StepperMotor* motor;
    void stepForward(unsigned int);
    void stepBackward(unsigned int);
  public:
    SortingPlate(Adafruit_StepperMotor*);
    bool ready();
    void reset();
    void rotateCCW(unsigned int);
    void rotateCW();
    int continueMoving();
};

#endif//SORTINGPLATE_H
