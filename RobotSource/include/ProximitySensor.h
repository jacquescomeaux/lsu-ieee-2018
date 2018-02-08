#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

#include "SerialLink.h"

class ProximitySensor : private SerialLink {
  public:
    ProximitySensor();
    float getDistance();
};

#endif
