#include <MagnetArm.h>

void MagnetArm::magnetize() {
  magnet->run(FORWARD);
}

void MagnetArm::demagnetize() {
  magnet->run(RELEASE);
}

//MagnetArm::MagnetArm() {}
MagnetArm::MagnetArm(Adafruit_StepperMotor* mot, Adafruit_DCMotor* mag) :
  RPM(60),
  bot_target(0),
  top_target(900),
  total_steps(1000),
  position(0),
  target_position(0),
  motor(mot),
  magnet(mag) {
  motor->setSpeed(RPM);
  magnet->run(RELEASE);
  magnet->setSpeed(255);
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

void MagnetArm::storeToken() {
  demagnetize();
}
