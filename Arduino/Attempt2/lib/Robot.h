#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"
//#include "Coord.h"
//#include "Drivetrain.h"
//#include "SensorRing.h"
//#include "ProximitySensor.h"
//#include "LineFollower.h"
//#include "SortingSystem.h"

class Robot {//: public Drivetrain, public LineFollower {
  //private:
   // Coord location;
   // SensorRing line_sensor_array;
   // ProximitySensor prox_sensors[4];
  public:
    Robot();
    //Coord getLocation();
    //void setLocation(Coord);
};

/*class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
    SortingSystem sorter;
};
*/
#endif
