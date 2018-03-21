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
    MotorShield motor_shields[3]; 
  private:
    Flag flags;
    const int NUM_TASKS;
    int last_ran[6];
    Fixed XP, YP, RotP, base_speed, veer_amount, acceleration;
    Direction current_direction;
    Wheel wheels[4];
    Fixed current_wheel_pos[4], target_wheel_pos[4];
    ProximitySensor edge_detectors[4];
    LineSensor line_sensor;
    void resolveDirection(Direction, Fixed* x, Fixed* y, Fixed* rot);
    void checkEdges();
    void checkDestination();	
    void setWheelSpeeds(const Fixed*);
    void adjustWheelSpeeds(const Fixed*);
    void correctWheelSpeeds(const Fixed*);
    void correctErrors();
    void ReportWheelSpeeds(); //print current wheel speeds for debugging
  public:
    Robot();

    bool debug;

    //stop immediately
    void stop();

    //to be called in a loop
    void update();

    //centering on intersection
    void center(int);
    
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
