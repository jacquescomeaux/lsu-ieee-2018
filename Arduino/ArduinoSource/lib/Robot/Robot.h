#ifndef ROBOT_H
#define ROBOT_H

#include <Direction.h>
#include <Fixed.h>
#include <Flag.h>

#include <SortingSystem.h>

#include <MotorShield.h>
#include <Wheel.h>
#include <ProximitySensor.h>
#include <LineSensor.h>

class Robot {
  protected:
    MotorShield motor_shields[2]; 
  private:
    Flag flags;
    const int NUM_TASKS;
    int last_ran[6];
    const Fixed SQRT_HALF, ZERO;
    Fixed XP, YP, RotP, base_speed, veer_amount, acceleration;
    Direction current_direction;
    Wheel wheels[4];
    Fixed current_wheel_pos[4], target_wheel_pos[4];
    ProximitySensor edge_detectors[4];
    LineSensor line_sensor;
    void checkEdges();
    void setWheelSpeeds(const Fixed*);
    void adjustWheelSpeeds(const Fixed*);
    void correctWheelSpeeds(const Fixed*);
    void checkDestination();	
    void correctErrors();
  public:
    Robot();
    //stop immediately
    void stop();

    //to be called in a loop
    void update();
    
    //move indefinitely
    void move(Direction);
    void move(Direction, Fixed speed);
    void move(Fixed x, Fixed y, Fixed rot);
   
    //adjust direction of movement
    void veer(Direction);
    void veer(Direction, Fixed amount);
    void veer(Fixed x, Fixed y, Fixed rot);
   
    //move a set amount
    void travel(Direction, Fixed dist);
    void travel(Direction, Fixed speed, Fixed dist);
    void travel(Fixed x, Fixed y, Fixed rot, Fixed dist);
  
    //change robot state
    void toggle(Flag);
    void adjustXP(Fixed);
    void adjustYP(Fixed);
    void adjustRotP(Fixed);
    void adjustBaseSpeed(Fixed);
};

class SortBot : public Robot, public SortingSystem {
//  private:
  //  MotorShield motor_shields[2];
  public:
    SortBot();
};

#endif//ROBOT_H
