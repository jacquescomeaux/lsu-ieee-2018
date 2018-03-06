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
    Fixed KP, KD, base_speed, veer_amount, acceleration;
    MotorShield motor_shields[2]; 
    Wheel wheels[4];
	long currentWheelPosition[4];
	long targetWheelPosition[4];
    //LineSensor line_sensor;
    //ProximitySensor edge_detectors[4];
    void checkEdges();
    void setWheelSpeeds(const Fixed*);
    void adjustWheelSpeeds(const Fixed*);
	void checkDestination();	
    //void observeErrors();
    //void correctErrors();
  public:
    Robot();
    void stop();
    void update();
    void move(Direction);
    void move(Direction, Fixed speed);
    void move(Fixed x, Fixed y, Fixed rot);
    void veer(Direction);
    void veer(Direction, Fixed amount);
    void veer(Fixed x, Fixed y, Fixed rot);
    void moveSetDistance(Direction, int);
    //void moveSetDistance(Direction, int, Fixed);
    //void followLine(Direction);
    //void followLine(Direction, int);
    //void toggle(Flag);
    void toggleMultiple(Flag);
    void adjustKD(Fixed);
    void adjustKP(Fixed);
    void adjustBaseSpeed(Fixed);
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif//ROBOT_H
