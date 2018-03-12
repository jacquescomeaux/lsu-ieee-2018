#include <MotorShield.h>

MotorShield::MotorShield() : AFMS() {
  AFMS.begin();
}

MotorShield::MotorShield(uint8_t addr) : AFMS(addr) {
  AFMS.begin();
}

MotorShield::MotorShield(uint8_t addr, uint16_t freq) : AFMS(addr) {
  AFMS.begin(freq);
}

Adafruit_DCMotor* MotorShield::getMotor(uint8_t n){//  const {
  return AFMS.getMotor(n);
} 

Adafruit_StepperMotor* getStepper(uint16_t steps, uint8_t n) {
  return AFMS.getStepper(steps, n);
}
