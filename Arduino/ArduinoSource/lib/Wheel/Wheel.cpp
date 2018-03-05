#include <Wheel.h>

Wheel::Wheel(Adafruit_DCMotor* m, int EncoderPin1, int EncoderPin2) : motor(m), Encoder encoder(EncoderPin1, EncoderPin2), speed(0), desired_speed(0), corrected_speed(0), direction_set(false) {
  motor->run(RELEASE);
  resetPosition();
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

void Wheel::incrementSpeed(int adjustment) {
  corrected_speed += adjustment;
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

float Wheel::convertDistance(const int &pos, bool feet = false) { //converts encoder reading into inches/feet (inches by default)
	float dist = pos * ECV;

	if (feet) {
		dist = dist * 12;
	}

	return dist;
}

float Wheel::getEncoderSpeed() {
	int CurrentPosition = getPosition();
	int PositionElapsed = CurrentPosition - LastPosition;
	float TimeElapsed = CurrentPositionTime - LastPositionTime;
	TimeElapsed = TimeElapsed / 1000; //convert to seconds

	float dist = convertDistance(PositionElapsed, true); //get distance traveled in feet
}


