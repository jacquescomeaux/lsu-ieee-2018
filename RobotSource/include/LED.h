#ifndef LED_H
#define LED_H

#include "SerialLink.h"

class LED : private SerialLink {
  private:
    bool on;
  public:
    LED();
    void setState(/*LEDSTATE*/);
    bool isOn();
};

#endif
