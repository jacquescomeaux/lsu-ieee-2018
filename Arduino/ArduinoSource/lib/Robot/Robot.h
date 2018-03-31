#ifndef ROBOT_H
#define ROBOT_H

#include <Direction.h>
#include <Fixed.h>
#include <Flag.h>

#include <SortingSystem.h>

#include <MotorShield.h>
#include <ProximitySensor.h>

class Robot : public Drivetrain, public LineFollower {
  private:
    bool stopped;
    unsigned int current_offset, current_range;
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
};

class SortBot : public Robot, public SortingSystem {
  public:
    SortBot();
    void update();
};

#endif//ROBOT_H
