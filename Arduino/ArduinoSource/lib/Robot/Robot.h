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
  private:
    //uint8_t flags;
    Flag flags;
    const int NUM_TASKS;
    const int last_ran[NUM_TASKS];
    const Fixed SQRT_HALF, ZERO;
    Fixed XP, YP, RotP, base_speed, veer_amount, acceleration;
    MotorShield motor_shields[2]; 
    Wheel wheels[4];
    Fixed current_wheel_pos[4], target_wheel_pos[4];
    Direction current_direction;
    //LineSensor line_sensor;
    //ProximitySensor edge_detectors[4];
    void checkEdges();
    void setWheelSpeeds(const Fixed*);
    void adjustWheelSpeeds(const Fixed*);
    void correctWheelSpeeds(const Fixed*);
    void checkDestination();	
    //void observeErrors();
    void correctErrors();
  public:
    Robot();
    void stop();
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
    void travel(Direction, Fixed speed, Fixed dist)
    void travel(Fixed x, Fixed y, Fixed rot, Fixed dist);
   
    //follow a line
    //void follow(Direction);
    //void follow(Direction, Fixed speed);
    //void follow(Fixed x, Fixed y, Fixed rot);
    //void moveSetDistance(Direction, int, Fixed);
    
    void toggle(Flag);
    void adjustXP(Fixed);
    void adjustYP(Fixed);
    void adjustRotP(Fixed);
    void adjustBaseSpeed(Fixed);
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif//ROBOT_H
