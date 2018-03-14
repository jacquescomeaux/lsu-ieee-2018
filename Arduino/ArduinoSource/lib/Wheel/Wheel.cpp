#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m, int enc_pin_1, int enc_pin_2) :
  tolerance(0.1),
  max_speed(255),
  ECV(0.000348755845),
  MS_TO_S(0.001),
  max_speed_uint8(255),
  forward(true),
  speed(0),
  goal_speed(0),
  correction(0),
  encoder(enc_pin_1, enc_pin_2),
  motor(m),
  current_pos(0), last_pos(0),
  current_time(1), last_time(0) {
    motor->run(RELEASE);
    resetPosition();
}

void Wheel::setMotorSpeed() {
  Fixed target = speed + correction;
  if(target > Fixed(0)) runForward();
  else runBackward();
  uint8_t motor_speed;
  if(target.mag() > max_speed) motor_speed = max_speed_uint8;
  else motor_speed = static_cast<uint8_t>(target.mag().getInt());
  motor->setSpeed(motor_speed);
}

void Wheel::runForward() {
//  if(forward) return;
  motor->run(FORWARD);
  forward = true;
}

void Wheel::runBackward() {
  //if(!forward) return;
  motor->run(BACKWARD);
  forward = false;
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

void Wheel::correctSpeed(Fixed c) {
  correction = c;
  setMotorSpeed();
}

void Wheel::approachSpeed(Fixed amount) {
  if((goal_speed - speed).mag() < amount) speed = goal_speed;
  else speed += (speed < goal_speed) ? amount : Fixed(0) - amount;  
  setMotorSpeed();
}

void Wheel::stop() {
  motor->run(RELEASE);
  motor->setSpeed(0);
  speed = Fixed(0);
  goal_speed = Fixed(0);
  correction = Fixed(0);
}

Fixed Wheel::getPosition() {
  return Fixed(static_cast<int>(encoder.read()));
}

void Wheel::resetPosition() {
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
