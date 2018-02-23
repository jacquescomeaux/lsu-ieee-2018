#ifndef ROBOT_H
#define ROBOT_H

#include <Direction.h>

#include <SortingSystem.h>

#include <MotorShield.h>
#include <Wheel.h>
#include <ProximitySensor.h>
#include <LineSensor.h>

class Robot {
  private:
    float KP, KD;
    const int default_speed;
    MotorShield motor_shields[2]; 
    Wheel wheels[4];
    const ProximitySensor edge_detectors[4];
    LineSensor line_sensors[8];
    bool following_line;
    Direction current_direction;
    int last_error;
    void setWheelSpeeds(Direction, int); 
    void correctErrors();
  public:
    Robot();
    void move(Direction);
    void move(Direction, int);
    void followLine(Direction);
    void followLine(Direction, int);
    void veerLeft();
    void veerRight();
    void speedUp();
    void slowDown();
    void stop();
    void checkEdges();
    void approachSpeed();
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif//ROBOT_H
