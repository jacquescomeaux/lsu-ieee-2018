#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Camera.h"
#include "Drivetrain.h"
#include "SensorRing.h"
#include "ProximitySensor.h"
#include "LineFollower.h"
#include "SortingSystem.h"
#include "Controller.h"

class Robot : public Drivetrain, public LineFollower {
  private:
    //Coord location;
    const Camera token_cam;
    const Camera location_cam;
    const SensorRing line_sensor_array;
    const ProximitySensor prox_sensors[4];
  public:
    Robot();
    const Controller control;
    //Coord getLocation() const;
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
};

#endif
