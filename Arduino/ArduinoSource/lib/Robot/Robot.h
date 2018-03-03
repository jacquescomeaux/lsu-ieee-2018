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
    int default_speed;
    MotorShield motor_shields[2]; 
    Wheel wheels[4];
    ProximitySensor edge_detectors[4];
    LineSensor line_sensors[2];
    bool following_line, calibrating, reading_sensors, edges;
    Direction current_direction;
    int last_error;
    int last_ran = 0;
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
    void toggleCalibration();
    void toggleSensorsOutput();
    void toggleEdgeOutput();
    void adjustDefaultSpeed(int);
    void adjustKP(float);
    void adjustKD(float);
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif//ROBOT_H
