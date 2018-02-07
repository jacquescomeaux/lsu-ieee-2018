#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include "Token.h"

class SortingSystem : private MagnetArm {
  private:
    MagnetArm token_arm;
    LED token_light;
    RGBSensor color_sensor;
    SortingPlate storage_plate, selector_plate;
  protected:
    SortingSystem();
  public:
    int checkTokenColor();
    void sortToken();
    void dropTokenStack();
};

#endif
