#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Direction.h"

#include "Drivetrain.h"
#include "LineFollower.h"
#include "SortingSystem.h"

#include "Camera.h"
#include "SensorRing.h"
#include "ProximitySensor.h"
#include "Controller.h"

class Robot : public Drivetrain, public LineFollower {
  private:
    //Coord location;
    Camera token_cam;
    Camera location_cam;
    const SensorRing line_sensor_array;
    const ProximitySensor prox_sensors[4];
  public:
    Robot();
    Coord getLocation() const;
    void moveUntilLine(Direction, int);
    void followUntilIntersection(Direction);
    bool tokenSeen() const;
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
    const Controller control;
};

#endif//ROBOT_H
