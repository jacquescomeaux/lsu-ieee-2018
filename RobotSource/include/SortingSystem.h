#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include "Color.h"
#include "Token.h"
#include <vector>

#include "MagnetArm.h"
#include "LED.h"
#include "RGBSensor.h"
#include "SortingPlate.h"


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
