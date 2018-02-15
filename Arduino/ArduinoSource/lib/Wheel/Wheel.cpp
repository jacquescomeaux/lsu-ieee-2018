#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m) {
  this->motor = m;
}

void Wheel::stop() {}
