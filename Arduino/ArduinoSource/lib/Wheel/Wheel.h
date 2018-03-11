#ifndef WHEEL_H
#define WHEEL_H

#define ENCODER_USE_INTERRUPTS
//#define ENCODER_OPTIMIZE_INTERRUPTS

//#define CPM		36032 //encoder ticks per revolution, multiplied by 10
//#define PiR2	12.56637 //wheel circumference

//Interrupt Pins Available: 2, 3, 18, 19, 20, 21

#include <Adafruit_MotorShield.h>
#include <Encoder.h>
#include <Fixed.h>

class Wheel {
  private:
    Adafruit_DCMotor* motor;
    Encoder encoder;
    Fixed speed, goal_speed, correction;
    //bool direction_set;
    const Fixed tolerance, max_speed, ECV, MS_TO_S;
    const uint8_t max_speed_uint8;
    Fixed current_pos, last_pos, current_time, last_time;
    Fixed convertDistance(Fixed, bool) const;
  public:
    Wheel(Adafruit_DCMotor*, int, int); 
    
    //goal speed
    void setSpeed(Fixed);
    void adjustSpeed(Fixed);
    void correctSpeed(Fixed);
    Fixed getSpeed() const;

    //motor interaction
    void approachSpeed(Fixed);
    void stop();
    
    //encoder
    Fixed getPosition();
    void resetPosition();
    Fixed getDistance();
    Fixed updateEncoderSpeed();

};

#endif//WHEEL_H
