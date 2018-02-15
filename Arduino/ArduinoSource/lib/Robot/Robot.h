#ifndef ROBOT_H
#define ROBOT_H

#include <Direction.h>
#include <MotorShield.h>
#include <Wheel.h>
#include <ProximitySensor.h>
#include <LineSensor.h>
#include <SortingSystem.h>


class Robot {
  private:
    const float KP, KD;
    const int default_speed;
    MotorShield motor_shields[2]; 
    Wheel wheels[4];
    ProximitySensor edge_detectors[4];
    LineSensor line_sensors[8];
    bool following_line;
    Direction current_direction;
    int last_error;
    void correctErrors();
  public:
    Robot();
    void move(Direction);
    void move(Direction, int);
    void followLine(Direction, int);
    void followLine(Direction);
    void stop();
    void checkEdges();
    void approachSpeed();
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif
