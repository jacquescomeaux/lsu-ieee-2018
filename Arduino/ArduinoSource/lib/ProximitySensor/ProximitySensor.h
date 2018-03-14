#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

class ProximitySensor {
  private:
    const unsigned long range_min, range_max;
    const unsigned int certainty_threshold;
    const int trig_pin, echo_pin;
    unsigned long proximity;
    unsigned int count;
    void updateProximity();
  public:
    ProximitySensor(int, int);
    ProximitySensor(int, int, float);
    float getProximity();
    bool edgeDetected();
};

#endif//PROXIMITYSENSOR_H
