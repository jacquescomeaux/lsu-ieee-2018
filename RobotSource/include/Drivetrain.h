#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "VelocityVector.h"

#include "SerialLink.h"

class Drivetrain : private SerialLink {
  private:
    const int nudge_speed;
  protected:
    Drivetrain();
  public:
    void stop() const;
    void move(VelocityVector) const;
    void nudge(VelocityVector, double);
    void travel(VelocityVector, double, bool);
};

#endif//DRIVETRAIN_H
