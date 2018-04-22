#ifndef ROBOT_H
#define ROBOT_H

#include <Fixed.h>
#include <Flag.h>
#include <VelocityVector.h>

#include <Drivetrain.h>
#include <LineFollower.h>
#include <SortingSystem.h>

#include <MotorShield.h>
#include <ProximitySensor.h>

class Robot : public Drivetrain, public LineFollower {
  private:
    bool stopped;
    unsigned int follow_offset, follow_range;
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
    
    //move a set distance
    void travel(VelocityVector, Fixed dist);
    void nudge(VelocityVector, Fixed dist);

    //change robot state
    void setFlags(Flag);
    void clearFlags(Flag);
    void toggleFlags(Flag);
    void setFollowOffset(unsigned int);
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
