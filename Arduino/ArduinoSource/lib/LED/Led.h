#ifndef LED_H
#define LED_H

enum class LED_STATE {
  OFF,
  ON
};

class LED {
  private:
    bool on;
  public:
    LED();
    void setState(LEDSTATE);
    void toggleState()
    bool isOn();
};

#endif