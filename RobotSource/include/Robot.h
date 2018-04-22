#ifndef ROBOT_H
#define ROBOT_H

#include "Coord.h"
#include "Direction.h"
#include "VelocityVector.h"

#include "Drivetrain.h"
#include "LineFollower.h"
#include "SortingSystem.h"

#include "Board.h"
#include "Camera.h"

class Robot : public Drivetrain, public LineFollower {
  private:
    Board* platform;
    Camera int_cam, location_cam;
    Coord location;
    int current_intersection;
    double base_speed;
    VelocityVector velocity;
    VelocityVector determineVelocityVector(Coord) const;
    VelocityVector resolveDirection(Direction) const;
    VelocityVector resolveDirection(Direction, double) const;
  public:
    Robot(Board*);
    Coord getLocation() const;
    void setSpeed(int);
    int getSpeed() const;
    void adjustSpeed(int);
    void move(Direction);
    void nudge(Direction, double);
    void travel(Direction, double, double, bool);
    void align(Direction, int);
    void followLine(Direction);
    bool moveUntilLine(Direction);
    bool moveUntilLine(VelocityVector);
    bool findIntersection(Direction);
    bool findIntersection(VelocityVector);
    bool followUntilIntersection(Direction);
    bool followUntilIntersection(VelocityVector);
    bool followWhileIntersection(Direction);
    bool followWhileIntersection(VelocityVector);
    bool tokenSeen();
    bool center();
    bool goToIntersection(int, bool centering);
    bool setCurrentIntersection(int int_num);
    void recover();
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot(Board*);
    int followPath(std::vector<int>&, bool);
};

#endif//ROBOT_H
