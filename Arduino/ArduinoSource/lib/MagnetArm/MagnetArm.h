#ifndef MAGNETARM_H
#define MAGNETARM_H

class MagnetArm {
  private:
    bool moving;
    void goToHeight(float) const;
    void magnetize() const;
    void demagnetize() const;
  public:
    MagnetArm();
    void reset() const;
    void pickUpToken() const;
    void storeToken() const;
    void dropTokens() const;
};

#endif//MAGNETARM_H
