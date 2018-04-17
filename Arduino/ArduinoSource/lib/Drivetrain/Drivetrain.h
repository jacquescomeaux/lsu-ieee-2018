#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

//#include <Direction.h>
#include <VelocityVector.h>

#include <Fixed.h>
#include <Flag.h>

#include <MotorShield.h>
#include <Wheel.h>

class Drivetrain {
  private:
    MotorShield wheel_shield; 
    Wheel wheels[4];
    Fixed starting_positions[4];
    Fixed steps_to_travel;
  protected:
    Fixed acceleration;
    Drivetrain();
    Flag checkDestination(bool);	
    void setWheelSpeeds(const Fixed*);
    void adjustWheelSpeeds(const Fixed*);
    void correctWheelSpeeds(const Fixed*);
  public:
    //stop immediately
    void stop();

    //to be called in a loop
    void approachSpeed();

    //move indefinitely
    void move(VelocityVector);
   
    //move a set amount with acceleration
    void travel(VelocityVector, Fixed dist);

    //move a set amount without acceleration
    void nudge(VelocityVector, Fixed dist);
  
    //permanently adjust direction of movement
    void steer(VelocityVector);
   
    //temporarily adjust direction of movement
    void veer(Fixed, Fixed, Fixed);
    void veer(VelocityVector);
   
    //change robot state
    void setAcceleration(Fixed);
    void adjustAcceleration(Fixed);
};

#endif//DRIVETRAIN_H
