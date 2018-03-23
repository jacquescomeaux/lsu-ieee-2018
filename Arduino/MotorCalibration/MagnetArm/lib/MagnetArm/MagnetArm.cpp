#include <MagnetArm.h>

void MagnetArm::magnetize() const {

}

void MagnetArm::demagnetize() const {}

MagnetArm::MagnetArm(Adafruit_StepperMotor* m) :
  RPM(30),
  bot_target(0),
  top_target(400),
  total_steps(440),
  position(440),
  motor(m) {
  motor->setSpeed(RPM);
}

void MagnetArm::goToHeight(int s) {
  Serial.print("Going to ");
  Serial.println(s);
  Serial.print("Position is ");
  Serial.println(position);
  if(s < 0 || s >= total_steps) return;
  if(s - position > 0) motor->step(static_cast<uint16_t>(s-position), FORWARD, SINGLE);
  else motor->step(static_cast<uint16_t>(-1*(s-position)), BACKWARD, SINGLE);
  motor->release();
  position = s;
}

void MagnetArm::reset() {
  demagnetize();
  goToHeight(top_target);
}

void MagnetArm::pickUpToken() {
  goToHeight(bot_target);
  magnetize();
  goToHeight(top_target);
}

void MagnetArm::storeToken() const {
  demagnetize();
}
