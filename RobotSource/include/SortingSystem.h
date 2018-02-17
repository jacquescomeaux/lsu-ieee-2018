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
    const MagnetArm token_arm;
    LED token_light;
    const RGBSensor color_sensor;
    SortingPlate storage_plate, selector_plate;
    Token* held_token;
    std::vector<Token*> token_stacks[7];
  protected:
    SortingSystem();
  public:
    void pickUpToken();
    Color checkTokenColor() const;
    void sortToken();
    void dropTokenStack(Color);
};

#endif
