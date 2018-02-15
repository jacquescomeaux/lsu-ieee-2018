#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m) {
  this->motor = m;
}

void Wheel::setSpeed(int speed) {
  this->desired_speed = speed;
}

void Wheel::adjustSpeed(int adjustment) {
  this->desired_speed += adjustment;
}

void Wheel::approachSpeed() {
  if(speed != desired_speed) {
    speed += (speed < desired_speed) ? 1 : -1;
    if(speed > 0) this->motor->run(FORWARD);
    else this->motor->run(BACKWARD);
    uint8_t motor_speed;
    if(speed > 255 || speed < -255) motor_speed = 255;
    else motor_speed = static_cast<uint8_t>(abs(speed));
    this->motor->setSpeed(motor_speed);
  }
}

void Wheel::stop() {
  this->motor->run(RELEASE);
}
