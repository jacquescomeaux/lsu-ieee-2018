#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

class ProximitySensor {
  private:
    const int trig_pin, echo_pin;
    const float cutoff;
    float proximity;//change to fixed
    void updateProximity();
    ProximitySensor();
  public:
    ProximitySensor(int, int);
    ProximitySensor(int, int, float);
    float getProximity();
    bool edgeDetected();
};

#endif//PROXIMITYSENSOR_H
