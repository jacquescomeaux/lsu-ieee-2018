#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m) : motor(m), speed(0), goal_speed(0), direction_set(false), tolerance(0.1) {
  motor->run(RELEASE);
}

void Wheel::setSpeed(Fixed s) {
  goal_speed = s;
}

Fixed Wheel::getSpeed() const {
  return speed;
}

void Wheel::adjustSpeed(Fixed adjustment) {
  goal_speed += adjustment;
}

void Wheel::approachSpeed(Fixed amount) {
  if(abs(goal_speed - speed) < tolerance) return;
  //needs damping factor
  speed += (speed < goal_speed) ? amount : Fixed(0) - amount;
  if(speed > 0) motor->run(FORWARD);
  else motor->run(BACKWARD);
  uint8_t motor_speed;
  if(abs(speed) > max_speed) motor_speed = max_speed;
  else motor_speed = static_cast<uint8_t>(abs(speed));
  motor->setSpeed(motor_speed);
}

void Wheel::stop() {
  motor->run(RELEASE);
  motor->setSpeed(0);
  speed = goal_speed = 0;
}
