#include <MagnetArm.h>

void MagnetArm::goToHeight(Fixed) const {}

void MagnetArm::magnetize() const {}

void MagnetArm::demagnetize() const {}

void MagnetArm::storeToken() const {}

MagnetArm::MagnetArm(Adafruit_StepperMotor* m) {
  motor = m;
}

void MagnetArm::reset() const {}

void MagnetArm::pickUpToken() const {}

//void MagnetArm::dropTokens() const {}
