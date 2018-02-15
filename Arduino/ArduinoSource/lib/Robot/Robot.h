#ifndef ROBOT_H
#define ROBOT_H

#include <Wheel.h>
#include <ProximitySensor.h>
#include <LineSensor.h>
#include <SortingSystem.h>

enum class DIRECTION {
  FRONT,
  BACK,
  LEFT,
  RIGHT,
  FRONT_LEFT,
  FRONT_RIGHT,
  BACK_LEFT,
  BACK_RIGHT
};

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
    void approachSpeed();
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif
