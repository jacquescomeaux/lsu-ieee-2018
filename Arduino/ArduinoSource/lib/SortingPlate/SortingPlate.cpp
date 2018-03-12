#include <SortingPlate.h>

SortingPlate::SortingPlate(Adafruit_MotorShield*) :
  RPM(60),
  step_amount(25),
  target_step(250),
  total_steps(2000),
  ready(true),
  position(0),
  target_position(0),
  bottom_offset(0),
  motor(m) {
  motor->setSpeed(RPM);
}

void SortingPlate::stepForward(int s) {
  if(s < 0 || s >= 2000) return;
  motor->step(static_cast<uint16_t>(s), FORWARD, SINGLE);
}

void SortingPlate::stepBackward(int s) {
  if(s < 0 || s >= 2000) return;
  motor->step(static_cast<uint16_t>(s), BACKWARD, SINGLE);
}

void SortingPlate::ready() {
  return ready;
}

void SortingPlate::reset() {
  stepBackward((total_steps - bottom_offset) % total_steps);
  stepForward((total_steps - position) % total_steps);
  motor->release();
  position = 0;
  target_position = 0;
  bottom_offset = 0;
  ready = true;
}

void SortingPlate::rotateCW(int dst) {
  if(!ready) return;
  target_position += dst * target_step;
  target_position %= total_steps;
  ready = false;
}

void SortingPlate::rotateCCW() {
  if(!ready) return;
  stepBackward(target_step);
  motor->release();
  position -= target_step;
  position %= total_steps;
  target_position -= target_step;
  target_position %= total_steps;
  bottom_offset += target_step;
}

int SortingPlate::continueMoving() {
  if(ready) return 1;
  if((target_position - position) % total_steps < step_amount) {
    stepForward((target_position - position) % total_steps);
    position = target_position;
    motor->release();
    ready = true;
    return 1;
  }
  position += step_amount;
  stepForward(step_amount);
  return 0;
}
