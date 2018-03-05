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
    Fixed speed, goal_speed;
    //bool direction_set;
    const Fixed tolerance, max_speed, min_speed;
	long position, LastPosition, LastPositionTime, CurrentPositionTime;
	float ConvertDistance(int, bool) const;
  public:
    Wheel(Adafruit_DCMotor*, int, int); 
    void setSpeed(Fixed);
    Fixed getSpeed() const;
    void adjustSpeed(Fixed);
    void approachSpeed(Fixed);
    void stop();
	
	int getPosition();
	void resetPosition();
	float getDistance();

	float getEncoderSpeed();



};

#endif//WHEEL_H
