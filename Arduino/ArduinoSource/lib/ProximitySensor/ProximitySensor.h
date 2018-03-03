#ifndef PROXIMITYSENSOR_H
#define PROXIMITYSENSOR_H

class ProximitySensor {
  private:
    const int trig_pin, echo_pin;
    const float cutoff;
    float prevProx[20] = {0};
    float proximity;//change to fixed
    void updateProximity();
    ProximitySensor();
    int count;
  public:
    ProximitySensor(int, int);
    ProximitySensor(int, int, float);
    float getProximity();
    float getAvgProximity();
    bool edgeDetected();
};

#endif//PROXIMITYSENSOR_H
