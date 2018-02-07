#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

class ProximitySensor : private SerialLink {
  protected:
    ProximitySensor();
  public:
    float getDistance();
};

#endif
