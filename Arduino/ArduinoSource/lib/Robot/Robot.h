#ifndef ROBOT_H
#define ROBOT_H

#include <Wheel.h>
#include <ProximitySensor.h>
#include <LineSensor.h>
#include <SortingSystem.h>

class Robot {
  private:
    Wheel wheels[4];
    ProximitySensor edge_detectors[4];
    LineSensor line_sensors[8];
  public:
    Robot();
    //void move();
    void stop();
    void checkEdges();
};

class SortBot : public Robot, public SortingSystem {
  private:
    SortingSystem sorter;
  public:
    SortBot();
};

#endif
