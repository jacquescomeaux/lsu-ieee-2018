#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class Drivetrain : private Wheel, private SerialLink {
  private:
    Wheel wheels[4];
  protected:
    Drivetrain();
};

#endif
