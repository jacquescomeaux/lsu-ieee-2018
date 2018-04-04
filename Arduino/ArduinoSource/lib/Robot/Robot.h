#ifndef ROBOT_H
#define ROBOT_H

#include <Fixed.h>
#include <Flag.h>

#include <Drivetrain.h>
#include <LineFollower.h>
#include <SortingSystem.h>

#include <MotorShield.h>
#include <ProximitySensor.h>

class Robot : public Drivetrain, public LineFollower {
  private:
    bool stopped;
    unsigned int center_offset, follow_range;
    Flag flags;
    ProximitySensor edge_detectors[4];
    void checkEdges();
  public:
    Robot();

    bool ready();

    //stop immediately
    void stop();

    //to be called in a loop
    void update();
    
    //
    void travel(Direction, Fixed dist);
    void travel(Direction, Fixed speed, Fixed dist);
    void travel(Fixed x, Fixed y, Fixed rot, Fixed dist);
    
    void nudge(Direction, Fixed dist);
    void nudge(Fixed x, Fixed y, Fixed rot, Fixed dist);

    //change robot state
    void setFlags(Flag);
    void clearFlags(Flag);
    void toggle(Flag);
    void setCenterOffset(unsigned int);
    void setFollowRange(unsigned int);
    void setTravelStop(bool);
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
    void update();
    void stop();
};

#endif//ROBOT_H
