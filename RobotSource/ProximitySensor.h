#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

class ProximitySensor : private SerialLink {
  public:
    ProximitySensor();
    float getDistance();
};

#endif
