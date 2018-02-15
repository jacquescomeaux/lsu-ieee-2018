#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include "Token.h"
#include "Color.h"
#include "MagnetArm.h"
#include "LED.h"
#include "RGBSensor.h"
#include "SortingPlate.h"

#include <vector>

class SortingSystem {
  private:
    MagnetArm token_arm;
    LED token_light;
    RGBSensor color_sensor;
    SortingPlate storage_plate, selector_plate;
    std::vector<Token> tokens;
  protected:
    SortingSystem();
  public:
    void pickUpToken();
    Color checkTokenColor();
    void sortToken();
    void dropTokenStack(Color);
};

#endif
