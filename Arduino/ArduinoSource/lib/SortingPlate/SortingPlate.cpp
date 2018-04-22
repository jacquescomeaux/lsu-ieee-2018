#include <SortingPlate.h>

SortingPlate::SortingPlate(Adafruit_StepperMotor* m) :
  RPM(450),
  step_amount(10),
  target_step(250),
  total_steps(2000),
  moving(false),
  position(0),
  target_position(0),
  bottom_offset(0),
  motor(m) {
  motor->setSpeed(RPM);
  motor->release();
}

void SortingPlate::stepForward(unsigned int s) {
  motor->step(static_cast<uint16_t>(s), FORWARD, DOUBLE);
}

void SortingPlate::stepBackward(unsigned int s) {
  motor->step(static_cast<uint16_t>(s), BACKWARD, DOUBLE);
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

void SortingPlate::rotateCCW(unsigned int dst) {
  if(moving) return;
  target_position += dst * target_step;
  target_position %= total_steps;
  moving = true;
}

void SortingPlate::rotateCW() {
  if(moving) return;
  stepForward(target_step + 10);
  motor->release();
  position += total_steps;
  position -= target_step;
  position %= total_steps;
  target_position += total_steps;
  target_position -= target_step;
  target_position %= total_steps;
  bottom_offset += target_step;
  bottom_offset %= total_steps;
}

int SortingPlate::continueMoving() {
  if(!moving) return 1;
  if((target_position - position + total_steps) % total_steps < step_amount) {
    stepBackward((target_position - position + total_steps) % total_steps);
    position = target_position;
    motor->release();
    moving = false;
    return 1;
  }
  position += step_amount;
  position %= total_steps;
  stepBackward(step_amount);
  return 0;
}
