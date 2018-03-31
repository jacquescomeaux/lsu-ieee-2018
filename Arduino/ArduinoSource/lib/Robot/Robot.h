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
    unsigned int current_offset, follow_range;
    Flag flags;
    ProximitySensor edge_detectors[3];
    void checkEdges();
  public:
    Robot();

    bool ready();

    //stop immediately
    void stop();

    //to be called in a loop
    void update();

    //change robot state
    void toggle(Flag);
    void setCenterOffset(unsigned int);
    void setFollowRange(unsigned int);
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
    void update();
};

#endif//ROBOT_H
