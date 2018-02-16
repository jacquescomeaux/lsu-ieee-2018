#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m) : motor(m), speed(0), desired_speed(0), correction(0), direction_set(false) {
  motor->run(RELEASE);
}

void Wheel::setSpeed(int s) {
  desired_speed = s;
}

void Wheel::adjustSpeed(int adjustment) {
  this->correction = adjustment;//adjustment->this->desired_speed += adjustment;
}

void Wheel::approachSpeed() {
  if(this->speed != this->desired_speed) {
    //Serial.println("WOWOWO");
    //if(speed + correction == 0) direction_set = false;
    speed += (speed < desired_speed) ? 1 : -1;
    //if(!direction_set) {
      //direction_set = true;
      if(speed + correction > 0) this->motor->run(FORWARD);
      else this->motor->run(BACKWARD);
    //}//
    uint8_t motor_speed;
    if(speed + correction > 200 || speed + correction < -200) motor_speed = 200;
    else motor_speed = static_cast<uint8_t>(abs(speed + correction));
    this->motor->setSpeed(motor_speed);
  }
}

void Wheel::stop() {
  motor->run(RELEASE);
  motor->setSpeed(0);
  speed = desired_speed = 0;
}
