#ifndef SORTINGPLATE_H
#define SORTINGPLATE_H

#include <Adafruit_MotorShield.h>
#include <Fixed.h>

class SortingPlate {
  private:
    const uint16_t RPM;
    const int step_amount, target_step, total_steps;
    bool ready;
    int position;
    int target_position;
    int bottom_offset;
    Adafruit_MotorShield* motor;
    void stepForward();
    void stepBackward();
  public:
    SortingPlate(Adafruit_MotorShield*);
    bool ready();
    void reset();
    void rotateCW(int);
    void rotateCCW();
    int continueMoving();
};

#endif//SORTINGPLATE_H
