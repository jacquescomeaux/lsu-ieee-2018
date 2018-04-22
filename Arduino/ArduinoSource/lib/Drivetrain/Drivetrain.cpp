#include <Drivetrain.h>

Drivetrain::Drivetrain() :
  wheel_shield(MotorShield(0x61)), //wheels
  wheels {
    //Interrupt Pins: 2, 3, 18, 19, 20, 21
    Wheel(wheel_shield.getMotor(1),  2, 4), //FRONT_LEFT
    Wheel(wheel_shield.getMotor(2),  3, 5), //BACK_LEFT
    Wheel(wheel_shield.getMotor(3), 18, 16), //BACK_RIGHT
    Wheel(wheel_shield.getMotor(4), 19, 17)  //FRONT_RIGHT
  },
  steps_to_travel(Fixed(0)),
  acceleration(Fixed(20)) {}

Flag Drivetrain::checkDestination(bool stopping) {
  for(int i = 0; i < 2; i++) { //only two encoders working
    if((wheels[i].getPosition() - starting_positions[i]).mag() < steps_to_travel) continue;
    if(stopping) stop();
    Serial.write('+');
    return Flag::TRAVELLING;
  }
  return Flag::NONE;
}

void Drivetrain::setWheelSpeeds(const Fixed* speeds) {
  for(int i = 0; i < 4; i++) wheels[i].setSpeed(speeds[i]);
}

void Drivetrain::adjustWheelSpeeds(const Fixed* speeds) {
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed(speeds[i]);
}

void Drivetrain::correctWheelSpeeds(const Fixed* speeds) {
  for(int i = 0; i < 4; i++) wheels[i].correctSpeed(speeds[i]);
}

void Drivetrain::approachSpeed() {
  for(Wheel& w : wheels) w.approachSpeed(acceleration);
}

void Drivetrain::stop() {
  for(Wheel& w : wheels) w.stop();
}


void Drivetrain::move(VelocityVector v) {
  const Fixed speeds[4] = {v.y + v.x - v.rot, v.y - v.x - v.rot, v.y + v.x + v.rot, v.y - v.x + v.rot};
  setWheelSpeeds(speeds);
}

void Drivetrain::travel(VelocityVector v, Fixed dist) {
  static const Fixed STEPS_PER_INCH = 286.7, ZERO = 0;
  Fixed x = v.x;
  Fixed y = v.y;
  Fixed rot = v.rot;
  if(dist < ZERO) {
    x = ZERO - x;
    y = ZERO - y;
    rot = ZERO - rot;
    dist = ZERO - dist;
  }
  VelocityVector vv(x, y, rot);
  steps_to_travel = dist * STEPS_PER_INCH;
  //for(Wheel& w : wheels) w.resetPosition();
  for(int i = 0; i < 2; i++) starting_positions[i] = wheels[i].getPosition();
  move(vv);
}

void Drivetrain::nudge(VelocityVector v, Fixed dist) {
  static const Fixed STEPS_PER_INCH = 286.7, ZERO = 0;
  Fixed x = v.x;
  Fixed y = v.y;
  Fixed rot = v.rot;
  if(dist < ZERO) {
    x = ZERO - x;
    y = ZERO - y;
    rot = ZERO - rot;
    dist = ZERO - dist;
  }
  VelocityVector vv(x, y, rot);
  steps_to_travel = dist * STEPS_PER_INCH;
  //for(Wheel& w : wheels) w.resetPosition();
  for(int i = 0; i < 2; i++) starting_positions[i] = wheels[i].getPosition();
  veer(vv);
}

void Drivetrain::steer(VelocityVector v) {
  const Fixed adjustments[4] = {v.y + v.x - v.rot, v.y - v.x - v.rot, v.y + v.x + v.rot, v.y - v.x + v.rot};
  adjustWheelSpeeds(adjustments);
}

void Drivetrain::veer(Fixed x, Fixed y, Fixed rot) {
  const Fixed adjustments[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  correctWheelSpeeds(adjustments);
}

void Drivetrain::veer(VelocityVector v) {
  const Fixed adjustments[4] = {v.y + v.x - v.rot, v.y - v.x - v.rot, v.y + v.x + v.rot, v.y - v.x + v.rot};
  correctWheelSpeeds(adjustments);
}

void Drivetrain::setAcceleration(Fixed acc) {
  acceleration = acc;
}

void Drivetrain::adjustAcceleration(Fixed adjustment) {
  acceleration += adjustment;
}
