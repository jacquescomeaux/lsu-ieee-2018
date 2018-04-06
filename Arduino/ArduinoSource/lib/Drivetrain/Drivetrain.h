#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Direction.h>
#include <Fixed.h>
#include <Flag.h>

#include <MotorShield.h>
#include <Wheel.h>

class Drivetrain {
  private:
    MotorShield wheel_shield; 
    Wheel wheels[4];
    //Fixed current_wheel_pos[4], target_wheel_pos[4];
    Fixed starting_positions[4];
    Fixed steps_to_travel;
  protected:
    Fixed base_speed, veer_amount, acceleration;
    Drivetrain();
    Direction current_direction;
    void resolveDirection(Direction, Fixed* x, Fixed* y, Fixed* rot);
    Flag checkDestination(bool);	
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
   
    //move a set amount
    void nudge(Fixed x, Fixed y, Fixed rot, Fixed dist);
    void travel(Fixed x, Fixed y, Fixed rot, Fixed dist);
  
    //permanently adjust direction of movement
    void steer(Direction);
    void steer(Direction, Fixed amount);
    void steer(Fixed x, Fixed y, Fixed rot);
   
    //temporarily adjust direction of movement
    void veer(Direction);
    void veer(Direction, Fixed amount);
    void veer(Fixed x, Fixed y, Fixed rot);
   
    //change robot state
    void setBaseSpeed(Fixed);
    void adjustBaseSpeed(Fixed);
    void setVeerAmount(Fixed);
    void adjustVeerAmount(Fixed);
    void setAcceleration(Fixed);
    void adjustAcceleration(Fixed);
};

#endif//DRIVETRAIN_H
