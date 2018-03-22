#include <SortingPlate.h>

SortingPlate::SortingPlate() {}
SortingPlate::SortingPlate(Adafruit_StepperMotor* m) :
  RPM(60),
  step_amount(25),
  target_step(250),
  total_steps(2000),
  moving(false),
  position(0),
  target_position(0),
  bottom_offset(0),
  motor(m) {
  motor->setSpeed(RPM);
}

void SortingPlate::stepForward(int s) {
  if(s < 0 || s >= total_steps) return;
  motor->step(static_cast<uint16_t>(s), FORWARD, SINGLE);
}

void SortingPlate::stepBackward(int s) {
  if(s < 0 || s >= total_steps) return;
  motor->step(static_cast<uint16_t>(s), BACKWARD, SINGLE);
}

bool SortingPlate::ready() {
  return !moving;
}

void SortingPlate::reset() {
  stepBackward((total_steps - bottom_offset) % total_steps);
  stepForward((total_steps - position) % total_steps);
  motor->release();
  position = 0;
  target_position = 0;
  bottom_offset = 0;
  moving = false;
}

void SortingPlate::rotateCW(int dst) {
  if(moving) return;
  target_position += dst * target_step;
  target_position %= total_steps;
  moving = true;
}

void SortingPlate::rotateCCW() {
  if(moving) return;
  stepBackward(target_step);
  motor->release();
  position -= target_step;
  position %= total_steps;
  target_position -= target_step;
  target_position %= total_steps;
  bottom_offset += target_step;
}

int SortingPlate::continueMoving() {
  if(!moving) return 1;
  if((target_position - position) % total_steps < step_amount) {
    stepForward((target_position - position) % total_steps);
    position = target_position;
    motor->release();
    moving = false;
    return 1;
  }
  position += step_amount;
  stepForward(step_amount);
  return 0;
}
