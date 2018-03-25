#include <MagnetArm.h>

void MagnetArm::magnetize() const {

}

void MagnetArm::demagnetize() const {}

MagnetArm::MagnetArm(Adafruit_StepperMotor* m) :
  RPM(60),
  bot_target(0),
  top_target(400),
  total_steps(540),
  target_position(0),
  motor(m) {
  motor->setSpeed(RPM);
}

void MagnetArm::goToHeight(int s) {
  if(s < 0 || s >= total_steps) return;
  if(s - position > 0) motor->step(static_cast<uint16_t>(s), FORWARD, SINGLE);
  else motor->step(static_cast<uint16_t>(-1*s), BACKWARD, SINGLE);
}

void MagnetArm::reset() {
  demagnetize();
  goToHeight(top_target);
  motor->release();
  position = top_target;
  target_position = top_target;
}

void MagnetArm::pickUpToken() {
  goToHeight(bot_target);
  magnetize();
  goToHeight(top_target);
  position = top_target;
  target_position = top_target;
}

void MagnetArm::storeToken() const {
  demagnetize();
}