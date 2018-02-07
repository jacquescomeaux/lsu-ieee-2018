#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"

class Robot {
  private:
    Coord location;
  public:
    Robot();
    Coord getLocation();
    void setLocation(Coord);
    Camera noir_cam;
    Camera lgtc_cam;
    Drivetrain drivetrain;
    SensorRing line_sensor_array;
    ProximitySensor prox_sensor;
    LineFollower line_follower;
};

class SortBot : public Robot {
  public:
    SortBot();
    SortingSystem sorter;
};

#endif
