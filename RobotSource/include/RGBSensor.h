#ifndef RGBSENSOR_H
#define RGBSENSOR_H

#include "Color.h"

class RGBSensor {
  protected:
    RGBSensor();
  public:
    Color getColor();
};

#endif
