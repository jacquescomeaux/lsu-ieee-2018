#ifndef MAGNETARM_H
#define MAGNETARM_H

#include "SerialLink.h"

class MagnetArm : private SerialLink {
  private:
    void goToHeight(float);
    void magnetize();
    void demagnetize();
  public:
    MagnetArm();
    void reset();
    void pickUpToken();
    void storeTokens();
    void dropTokens();
};

#endif
