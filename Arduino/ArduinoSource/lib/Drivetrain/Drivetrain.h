#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Direction.h>
#include <Fixed.h>

#include <MotorShield.h>
#include <Wheel.h>

class Drivetrain {
  private:
    MotorShield wheel_shield; 
    Fixed base_speed, veer_amount, acceleration;
    Wheel wheels[4];
    Fixed current_wheel_pos[4], target_wheel_pos[4];
  protected:
    Drivetrain();
    Direction current_direction;
    bool travelDstReached; //tracks if travel has been completed
    void resolveDirection(Direction, Fixed* x, Fixed* y, Fixed* rot);
    void checkDestination();	
    void setWheelSpeeds(const Fixed*);
    void adjustWheelSpeeds(const Fixed*);
    void correctWheelSpeeds(const Fixed*);
    void reportWheelSpeeds(); //print current wheel speeds for debugging
    bool inMotion();
  public:
    //stop immediately
    void stop();

    //to be called in a loop
    void approachSpeed();

    //move indefinitely
    void move(Direction);
    void move(Direction, Fixed speed);
    void move(Fixed x, Fixed y, Fixed rot);
   
    //temporarily adjust direction of movement
    void veer(Direction);
    void veer(Direction, Fixed amount);
    void veer(Fixed x, Fixed y, Fixed rot);
   
    //permanently adjust direction of movement
    void steer(Direction);
    void steer(Direction, Fixed amount);
    void steer(Fixed x, Fixed y, Fixed rot);
   
    //move a set amount
    void travel(Direction, Fixed dist);
    void travel(Direction, Fixed speed, Fixed dist);
    void travel(Fixed x, Fixed y, Fixed rot, Fixed dist);
  
    //change robot state
    void adjustBaseSpeed(Fixed);
    void adjustVeerAmount(Fixed);
    void adjustAcceleration(Fixed);
};

#endif//DRIVETRAIN_H
