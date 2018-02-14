#ifndef MAGNETARM_H
#define MAGNETARM_H

class MagnetArm {
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
