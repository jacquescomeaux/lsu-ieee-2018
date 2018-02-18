#ifndef RGBSENSOR_H
#define RGBSENSOR_H

#include "Color.h"

#include "SerialLink.h"

class RGBSensor : private SerialLink {
  public:
    RGBSensor();
    Color getColor() const;
};

#endif
