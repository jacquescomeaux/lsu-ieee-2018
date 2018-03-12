#ifndef MAGNETARM_H
#define MAGNETARM_H

#include <Adafruit_MotorShield.h>
#include <Fixed.h>

class MagnetArm {
  private:
    Adafruit_MotorShield* motor;
    bool moving;
    void goToHeight(Fixed) const;
    void magnetize() const;
    void demagnetize() const;
  public:
    MagnetArm(Adafruit_MotorShield*);
    void reset() const;
    void pickUpToken() const;
    void storeToken() const;
    //void dropTokens() const;
};

#endif//MAGNETARM_H
