#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m) : motor(m), speed(0), desired_speed(0), corrected_speed(0), direction_set(false) {
  motor->run(RELEASE);
}

void Wheel::setSpeed(int s) {
  desired_speed = s;
  corrected_speed = s;
}

int Wheel::getSpeed() {
  return speed;
}

void Wheel::adjustSpeed(int adjustment) {
  //this->correction = adjustment;
  //corrected_speed = desired_speed + adjustment;
  corrected_speed += adjustment;
  //->this->desired_speed += adjustment;
}

void Wheel::approachSpeed() {
  if(this->speed != this->corrected_speed) {
    //Serial.println("WOWOWO");
    if(speed == 0) direction_set = false;
    speed += (speed < corrected_speed) ? 2 : -2;
    if(!direction_set) {
      direction_set = true;
      if(speed > 0) this->motor->run(FORWARD);
      else this->motor->run(BACKWARD);
    }
    uint8_t motor_speed;
    if(speed > 200 || speed < -200) motor_speed = 200;
    else motor_speed = static_cast<uint8_t>(abs(speed));
    this->motor->setSpeed(motor_speed);
  }
}

void Wheel::stop() {
  motor->run(RELEASE);
  motor->setSpeed(0);
  speed = corrected_speed = desired_speed = 0;
}
