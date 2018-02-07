#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Drivetrain.h"

class Robot : private Drivetrain, private SensorRing, private, ProximitySensor, private LineFollower {
  private:
    Coord location;
  public:
    Robot();
    Coord getLocation();
    void setLocation(Coord);
    Camera token_cam;
    Camera location_cam;
    Drivetrain drivetrain;
    SensorRing line_sensor_array;
    ProximitySensor prox_sensors[4];
    LineFollower line_follower;
};

class SortBot : public Robot, private SortingSystem {
  public:
    SortBot();
    SortingSystem sorter;
};

#endif
