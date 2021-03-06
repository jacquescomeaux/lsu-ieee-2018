#include <MagnetArm.h>

void MagnetArm::magnetize() {
  magnet->run(FORWARD);
}

void MagnetArm::demagnetize() {
  magnet->run(RELEASE);
}

MagnetArm::MagnetArm(Adafruit_StepperMotor* mot, Adafruit_DCMotor* mag) :
  RPM(30),
  bot_target(0),
  top_target(455),
  total_steps(460),
  position(455),
  motor(mot),
  magnet(mag) {
    motor->setSpeed(RPM);
    magnet->run(RELEASE);
    magnet->setSpeed(255);
}

void MagnetArm::goToHeight(int s) {
  Serial.print("Going to ");
  Serial.println(s);
  Serial.print("from ");
  Serial.println(position);
  Serial.println();
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
  goToHeight(bot_target);
  magnetize();
  goToHeight(top_target);
}

void MagnetArm::storeToken() {
  demagnetize();
}
