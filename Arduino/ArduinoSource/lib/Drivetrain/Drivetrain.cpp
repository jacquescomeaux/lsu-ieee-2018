#include <Drivetrain.h>

Drivetrain::Drivetrain() :
  wheel_shield(MotorShield(0x61)), //wheels
  current_direction(Direction::NONE),
  base_speed(Fixed(90)),
  veer_amount(Fixed(10)),
  acceleration(Fixed(20)), //previously set at 10
  wheels {
    //Interrupt Pins: 2, 3, 18, 19, 20, 21
    Wheel(motor_shields[0].getMotor(1),  2, 4), //FRONT_LEFT
    Wheel(motor_shields[0].getMotor(2),  3, 5), //BACK_LEFT
    Wheel(motor_shields[0].getMotor(3), 18, 16), //BACK_RIGHT
    Wheel(motor_shields[0].getMotor(4), 19, 17)  //FRONT_RIGHT
  } {}

void Drivetrain::resolveDirection(Direction dir, Fixed* x, Fixed* y, Fixed* rot) {
  static const Fixed ZERO = 0, POS_ONE = 1, NEG_ONE = -1, POS_SQRT_HALF = sqrt(0.5), NEG_SQRT_HALF = -1 * sqrt(0.5);
  auto assign = [&] (Fixed x_new, Fixed y_new, Fixed rot_new) {*x = x_new; *y = y_new; *rot = rot_new;};
  switch(dir) {
    case(Direction::NONE): assign(ZERO, ZERO, ZERO); break;
    case(Direction::FRONT): assign(ZERO, POS_ONE, ZERO); break;
    case(Direction::BACK):  assign(ZERO, NEG_ONE, ZERO); break;
    case(Direction::LEFT):  assign(NEG_ONE, ZERO, ZERO); break;
    case(Direction::RIGHT): assign(POS_ONE, ZERO, ZERO); break;
    case(Direction::FRONT_LEFT):  assign(NEG_SQRT_HALF, POS_SQRT_HALF, ZERO); break;
    case(Direction::FRONT_RIGHT): assign(POS_SQRT_HALF, POS_SQRT_HALF, ZERO); break;
    case(Direction::BACK_LEFT):   assign(NEG_SQRT_HALF, NEG_SQRT_HALF, ZERO); break;
    case(Direction::BACK_RIGHT):  assign(POS_SQRT_HALF, NEG_SQRT_HALF, ZERO); break;
    case(Direction::CLOCKWISE):         assign(ZERO, ZERO, NEG_ONE); break;
    case(Direction::COUNTER_CLOCKWISE): assign(ZERO, ZERO, POS_ONE); break;
    default: break;
  }
}

void Drivetrain::checkDestination() {
  for(int i = 0; i < 2; i++) {
    if((wheels[i].getSpeed() > Fixed(0)) != (wheels[i].getPosition() >= target_wheel_pos[i])) continue;
    flags &= ~Flag::TRAVEL_TO_DST;
    stop();
  }
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

void Drivetrain::stop() {
  for(Wheel& w : wheels) w.stop();
}

bool Drivetrain::inMotion() {
  if(wheels[0].getSpeed() + wheels[1].getSpeed() + wheels[2].getSpeed() + wheels[3].getSpeed() == Fixed(0)) return false;
  return true;
}

void Drivetrain::move(Direction dir) {
  move(dir, base_speed);
}

void Drivetrain::move(Direction dir, Fixed speed) {
  current_direction = dir;
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  move(speed * x, speed * y, speed * rot);
}

void Drivetrain::move(Fixed x, Fixed y, Fixed rot) {
  const Fixed speeds[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  setWheelSpeeds(speeds);
}

void Drivetrain::veer(Direction dir) {
  veer(dir, veer_amount);
}

void Drivetrain::veer(Direction dir, Fixed amount) {
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  veer(amount * x, amount * y, amount * rot);
}

void Drivetrain::veer(Fixed x, Fixed y, Fixed rot) {
  const Fixed adjustments[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  correctWheelSpeeds(adjustments);
}

void Drivetrain::steer(Direction dir) {
  steer(dir, veer_amount);
}

void Drivetrain::steer(Direction dir, Fixed amount) {
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  steer(amount * x, amount * y, amount * rot);
}

void Drivetrain::steer(Fixed x, Fixed y, Fixed rot) {
  const Fixed adjustments[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  adjustWheelSpeeds(adjustments);
}

void Drivetrain::travel(Direction dir, Fixed dist) {
  travel(dir, dist, base_speed);
}

void Drivetrain::travel(Direction dir, Fixed dist, Fixed speed) {
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  travel(speed * x, speed * y, speed * rot, dist);
}

void Drivetrain::travel(Fixed x, Fixed y, Fixed rot, Fixed dist) {
  static const Fixed STEPS_PER_INCH = 286.7, ZERO = 0, POS_ONE = 1, NEG_ONE = -1;
  Fixed steps_to_travel = dist * STEPS_PER_INCH;
  const Fixed speeds[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  for(int i = 0; i < 2; i++) target_wheel_pos[i] = wheels[i].getPosition() + steps_to_travel * ((speeds[i] > ZERO) ? POS_ONE : NEG_ONE);
  flags |= Flag::TRAVEL_TO_DST;
  setWheelSpeeds(speeds);
}

void Drivetrain::adjustBaseSpeed(Fixed adjustment) {
  base_speed += adjustment;
  //Serial.print("Speed = ");
  //Serial.println(base_speed.getInt());
}

void Drivetrain::adjustVeerAmount(Fixed adjustment) {
  veer_amount += adjustment;
}

void Drivetrain::adjustAcceleration(Fixed adjustment) {
  acceleration += adjustment;
}

void Drivetrain::reportWheelSpeeds() {
  for(int i = 0; i < 4; i++) {
    Fixed report = wheels[i].getActualSpeed();
   /* Serial.print("Wheel ");
    Serial.print(i);
    Serial.print("-->");
    Serial.println(report.getInt());*/
  }
}