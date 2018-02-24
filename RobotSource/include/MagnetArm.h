#ifndef MAGNETARM_H
#define MAGNETARM_H

#include "SerialLink.h"

class MagnetArm : private SerialLink {
  private:
    void goToHeight(float) const;
    void magnetize() const;
    void demagnetize() const;
  public:
    MagnetArm();
    void reset() const;
    void pickUpToken() const;
    void storeTokens() const;
    void dropTokens() const;
};

#endif
