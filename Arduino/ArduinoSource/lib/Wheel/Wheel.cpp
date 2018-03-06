#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m, int enc_pin_1, int enc_pin_2) : motor(m), encoder(enc_pin_1, enc_pin_2), speed(0), goal_speed(0), direction_set(false), tolerance(0.1), ECV(0.000348755845) {
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
  if(abs(goal_speed - speed) < tolerance) return;
  //needs damping factor
  speed += (speed < goal_speed) ? amount : Fixed(0) - amount;
  if(speed > Fixed(0)) motor->run(FORWARD);
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

int Wheel::getPosition() {
	LastPositionTime = CurrentPositionTime;
	CurrentPositionTime = millis();
	LastPosition = position;
	position = encoder.read();
	
	return position;
}

void Wheel::resetPosition() {
	LastPositionTime = 0;
	CurrentPositionTime = 0;
	LastPosition = 0;
	position = 0;
	encoder.write(0);
}

float Wheel::getDistance() { 
	int position = getPosition();
	float distanceTraveled = convertDistance(position, false);

	return distanceTraveled; //result in inches
}

float Wheel::convertDistance(int pos, bool feet = false) const { //converts encoder reading into inches/feet (inches by default)
	Fixed dist = pos * ECV;

	if (feet) {
		dist = dist * 12;
	}

	return dist;
}

float Wheel::getEncoderSpeed() {
	int CurrentPosition = getPosition();
	int PositionElapsed = CurrentPosition - LastPosition;
	Fixed TimeElapsed = CurrentPositionTime - LastPositionTime;
	TimeElapsed = TimeElapsed * 0.001; //convert to seconds

	Fixed dist = convertDistance(PositionElapsed, true); //get distance traveled in feet
	
	Fixed speed = dist / TimeElapsed;
}


