#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Direction.h"

#include "Drivetrain.h"
#include "LineFollower.h"
#include "SortingSystem.h"

#include "Board.h"
#include "Camera.h"
#include "Controller.h"

class Robot : public Drivetrain, public LineFollower {
  private:
    Board* platform;
    Coord location;
    int current_intersection;
    Camera int_cam, location_cam;
    int speed;
  public:
    Robot(Board*);
    Coord getLocation() const;
    void followLine(Direction) const;
    void setSpeed(int);
    void moveUntilLine(Direction, int);
    bool followUntilIntersection(Direction);
    bool tokenSeen();
    //bool center(bool, int);
    bool goToIntersection(int);
    bool setCurrentIntersection(int int_num);
    void recover();
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot(Board*);
    const Controller control;
    int followPath(std::vector<int>&, bool);
};

#endif//ROBOT_H
