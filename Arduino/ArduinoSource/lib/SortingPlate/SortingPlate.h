#ifndef SORTINGPLATE_H
#define SORTINGPLATE_H

#include <Adafruit_MotorShield.h>
#include <Fixed.h>

class SortingPlate {
  private:
    const uint16_t RPM;
    const int step_amount, target_step, total_steps;
    bool moving;
    int position, target_position, bottom_offset;
    Adafruit_StepperMotor* motor;
    void stepForward(int);
    void stepBackward(int);
  public:
    SortingPlate();
    SortingPlate(Adafruit_StepperMotor*);
    bool ready();
    void reset();
    void rotateCW(int);
    void rotateCCW();
    int continueMoving();
};

#endif//SORTINGPLATE_H
