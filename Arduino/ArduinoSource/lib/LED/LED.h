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
    void setState(LED_STATE);
    void toggleState();
    bool isOn();
};

#endif
