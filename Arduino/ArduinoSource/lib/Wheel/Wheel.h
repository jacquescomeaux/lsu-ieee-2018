#ifndef WHEEL_H
#define WHEEL_H

#define ENCODER_USE_INTERRUPTS
#define ENCODER_OPTIMIZE_INTERRUPTS
#define CPM		36032 //encoder ticks per revolution, multiplied by 10
#define PiR2	12.56637 //wheel circumference
#define ECV 0.00348755845 //Encoder Conversion Factor. Inches traveled per pulse
//Interrupt Pins Available: 2, 3, 18, 19, 20, 21

#include <Adafruit_MotorShield.h>
#include <Encoder.h>

class Wheel {
  private:
    Adafruit_DCMotor* motor;
	Encoder encoder;
	int speed, desired_speed, corrected_speed;
    bool direction_set;

	long position, LastPosition, LastPositionTime, CurrentPositionTime;
	float ConvertDistance(const int&, bool);
  public:
    Wheel(Adafruit_DCMotor*, int, int); 
    void setSpeed(int);
    int getSpeed() const;
    void adjustSpeed(int);
    void incrementSpeed(int);
    void approachSpeed();
    void stop();
	
	int getPosition();
	void resetPosition();
	float getDistance();

	float getEncoderSpeed();



};

#endif//WHEEL_H
