#ifndef ROBOT_H
#define ROBOT_H

#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Direction.h>
#include <ProximitySensor.h>
#include <LineSensor.h>
#include <SortingSystem.h>


class Robot : public Drivetrain {
  private:
    Adafruit_MotorShield AFMS[2];
    Wheel wheels[4];
    ProximitySensor edge_detectors[4];
    LineSensor line_sensors[8];
  public:
    Robot();
    void move(DIRECTION);
    void stop();
    void checkEdges();
    void approachSpeed();
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif
