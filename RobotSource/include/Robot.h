#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Direction.h"

#include "Drivetrain.h"
#include "LineFollower.h"
#include "SortingSystem.h"

#include "Camera.h"
#include "Controller.h"

class Robot : public Drivetrain, public LineFollower {
  private:
    //Coord location;
    Camera int_cam;//, location_cam;
    int speed;
  public:
    Robot();
    Coord getLocation() const;
    void followLine(Direction) const;
    void setSpeed(int);
    void moveUntilLine(Direction, int);
    bool followUntilIntersection(Direction);
    bool tokenSeen();
    bool center(bool, int);
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
    const Controller control;
};

#endif//ROBOT_H
