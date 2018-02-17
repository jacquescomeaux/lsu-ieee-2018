#ifndef LED_H
#define LED_H

#include "SerialLink.h"

class LED : private SerialLink {
  private:
    bool on;
  public:
    LED();
    enum class LED_STATE {OFF, ON};
    void setState(LED_STATE);
    bool isOn() const;
};

#endif
