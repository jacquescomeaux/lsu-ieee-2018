#include <MagnetArm.h>

void MagnetArm::magnetize() const {}

void MagnetArm::demagnetize() const {}

MagnetArm::MagnetArm(Adafruit_StepperMotor* m) :
  RPM(60),
  //step_amount(10),
  bot_target(0),
  //mid_target(500),
  top_target(900),
  total_steps(1000),
  //moving(false),
  position(0),
  target_position(0),
  motor(m) {
  motor->setSpeed(RPM);
}

void MagnetArm::goToHeight(int s) {
  if(s < 0 || s >= total_steps) return;
  if(s - position > 0) motor->step(static_cast<uint16_t>(s), FORWARD, SINGLE);
  else motor->step(static_cast<uint16_t>(-1*s), BACKWARD, SINGLE);
}
/*
bool MagnetArm::ready() {
  return !moving;
}*/

void MagnetArm::reset() {
  demagnetize();
  goToHeight(top_target);
  motor->release();
  position = top_target;
  target_position = top_target;
  //moving = false;
}

void MagnetArm::pickUpToken() {
  //if(moving) return;
  goToHeight(bot_target);
  magnetize();
  goToHeight(top_target);
  position = top_target;
  target_position = top_target;
}

void MagnetArm::storeToken() const {
  ///if(moving) return;
  demagnetize();
}

/*
int MagnetArm::continueMoving() {
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
}*/
