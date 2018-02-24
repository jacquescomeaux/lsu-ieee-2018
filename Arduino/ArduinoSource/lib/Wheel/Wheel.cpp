#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m) : motor(m), speed(0), desired_speed(0), corrected_speed(0), direction_set(false) {
  motor->run(RELEASE);
}

void Wheel::setSpeed(int s) {
  desired_speed = s;
  corrected_speed = s;
}

int Wheel::getSpeed() const {
  return speed;
}

void Wheel::adjustSpeed(int adjustment) {
  corrected_speed = desired_speed + adjustment;
}

void Wheel::approachSpeed() {
  if(speed != corrected_speed) {
    if(speed == 0) direction_set = false;
    speed += (speed < corrected_speed) ? 1 : -1;
    if(!direction_set) {
      direction_set = true;
      if(speed > 0) motor->run(FORWARD);
      else motor->run(BACKWARD);
    }
    uint8_t motor_speed;
    if(speed > 255 || speed < -255) motor_speed = 255;
    else motor_speed = static_cast<uint8_t>(abs(speed));
    motor->setSpeed(motor_speed);
  }
}

void Wheel::stop() {
  motor->run(RELEASE);
  motor->setSpeed(0);
  speed = corrected_speed = desired_speed = 0;
}
