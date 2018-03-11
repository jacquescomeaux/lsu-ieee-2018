#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m, int enc_pin_1, int enc_pin_2) :
  motor(m),
  encoder(enc_pin_1, enc_pin_2),
  speed(0),
  goal_speed(0),
  tolerance(0.1),
  max_speed(255),
  ECV(0.000348755845),
  MS_TO_S(0.001),
  max_speed_uint8(255),
  current_pos(0), last_pos(0),
  current_time(1), last_time(0) {
    motor->run(RELEASE);
    resetPosition();
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
  if((goal_speed - speed).mag() < tolerance) return;
  //needs damping factor
  speed += (speed < goal_speed) ? amount : Fixed(0) - amount;
  if(speed > Fixed(0)) motor->run(FORWARD);
  else motor->run(BACKWARD);
  uint8_t motor_speed;
  if(speed.mag() > max_speed) motor_speed = max_speed_uint8;
  else motor_speed = static_cast<uint8_t>(speed.mag().getInt());
  motor->setSpeed(motor_speed);
}

void Wheel::stop() {
  motor->run(RELEASE);
  motor->setSpeed(0);
  speed = goal_speed = Fixed(0);
}

Fixed Wheel::getPosition() {
  //lastPositionTime = currentPositionTime;
  //currentPositionTime = millis();
  //lastPosition = position;
  //position = encoder.read();
  //return position;
  return Fixed(static_cast<int>(encoder.read()));
}

void Wheel::resetPosition() {
  //LastPositionTime = 0;
  //CurrentPositionTime = 0;
  //LastPosition = 0;
  //position = 0;
  encoder.write(0);
}

Fixed Wheel::getDistance() { 
  Fixed position = getPosition();
  Fixed distanceTraveled = convertDistance(position, false);
  return distanceTraveled; //result in inches
}

//converts encoder reading into inches/feet (inches by default)
Fixed Wheel::convertDistance(Fixed pos, bool feet = false) const {
  Fixed dist = pos * ECV;
  if(feet) dist *= 12;
  return dist;
}

Fixed Wheel::updateEncoderSpeed() {
  Fixed current_pos = getPosition();
  Fixed current_time = static_cast<int>(millis());
  Fixed dist = convertDistance(current_pos - last_pos, true);
  Fixed time = MS_TO_S * (current_time - last_time);
  Fixed speed = dist / time;
  last_pos = current_pos;
  last_time = current_time;
  return speed;
}
