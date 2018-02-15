#ifndef ROBOT_H
#define ROBOT_H

#include <Direction.h>
#include <Drivetrain.h>
#include <ProximitySensor.h>
#include <LineSensor.h>
#include <SortingSystem.h>


class Robot : public Drivetrain {
  private:
    //Wheel wheels[4];
    ProximitySensor edge_detectors[4];
    LineSensor line_sensors[8];
  public:
    Robot();
    //void move(DIRECTION);
    //void stop();
    void checkEdges();
    void approachSpeed();
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif
