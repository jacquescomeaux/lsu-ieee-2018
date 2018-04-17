#ifndef WHEEL_H
#define WHEEL_H

#define ENCODER_USE_INTERRUPTS

#include <Adafruit_MotorShield.h>
#include <Encoder.h>
#include <Fixed.h>

class Wheel {
  private:
    const Fixed tolerance, max_speed, ECV, MS_TO_S;
    const uint8_t max_speed_uint8;
    bool forward;
    Fixed speed, goal_speed, correction;
    Encoder encoder;
    Adafruit_DCMotor* motor;
    Fixed current_pos, last_pos, current_time, last_time;
    Fixed convertDistance(Fixed, bool) const;
    void setMotorSpeed();
    void runForward();
    void runBackward();
  public:
    Wheel(Adafruit_DCMotor*, int, int); 
    
    //goal speed
    void setSpeed(Fixed);
    void adjustSpeed(Fixed);
    void correctSpeed(Fixed);
    Fixed getSpeed() const;
    Fixed getActualSpeed() const;

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
