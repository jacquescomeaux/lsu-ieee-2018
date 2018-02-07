#ifndef MAGNETARM_H
#define MAGNETARM_H

class MagnetArm : private SerialLink {
  private:
    void goToHeight(float);
    void magnetize();
    void demagnetize();
  protected:
    void storeTokens();
  public:
    MagnetArm();
    void reset();
    void pickUpToken();
    void dropTokens();
};

#endif
