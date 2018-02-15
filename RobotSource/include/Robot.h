#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Camera.h"
#include "Drivetrain.h"
#include "SensorRing.h"
#include "ProximitySensor.h"
#include "LineFollower.h"
#include "SortingSystem.h"

class Robot : public Drivetrain, public LineFollower {
  private:
    Coord location;
    Camera token_cam;
    Camera location_cam;
    SensorRing line_sensor_array;
    ProximitySensor prox_sensors[4];
  public:
    Robot();
    Coord getLocation();
    void setLocation(Coord);
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif
