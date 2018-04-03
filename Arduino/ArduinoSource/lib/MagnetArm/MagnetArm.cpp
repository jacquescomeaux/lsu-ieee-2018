#include <MagnetArm.h>

void MagnetArm::magnetize() {
  magnet->run(FORWARD);
}

void MagnetArm::demagnetize() {
  magnet->run(RELEASE);
}

MagnetArm::MagnetArm(Adafruit_StepperMotor* mot, Adafruit_DCMotor* mag) :
  RPM(60),
  bot_target(0),
  top_target(460),
  cam_target(300),
  total_steps(465),
  position(465),
  motor(mot),
  magnet(mag) {
    motor->setSpeed(RPM);
    magnet->run(RELEASE);
    magnet->setSpeed(210);
}

void MagnetArm::goToHeight(int s) {
  if(s < 0 || s >= total_steps) return;
  if(s - position > 0) motor->step(static_cast<uint16_t>(s-position), FORWARD, DOUBLE);
  else motor->step(static_cast<uint16_t>(-1*(s-position)), BACKWARD, DOUBLE);
  motor->release();
  position = s;
}

void MagnetArm::reset() {
  demagnetize();
  goToHeight(top_target);
}

void MagnetArm::pickUpToken() {
  magnetize();
  goToHeight(bot_target);
  delay(500);
  goToHeight(cam_target);
}

void MagnetArm::storeToken() {
  magnet->run(BACKWARD); //maybe short reverse in polarity will help it drop
  delay(50);
  demagnetize();
}

void MagnetArm::goToTop() {
  goToHeight(top_target);
}
