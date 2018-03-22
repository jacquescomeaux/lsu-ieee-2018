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
    const Camera token_cam;
    const Camera location_cam;
    const SensorRing line_sensor_array;
    const ProximitySensor prox_sensors[4];
  public:
    Robot();
    Coord getLocation() const;
    void moveUntilLine(Direction) const;
    void followUntilIntersection(Direction) const;
    void center() const;
    bool tokenSeen() const;
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
    const Controller control;
};

#endif//ROBOT_H
