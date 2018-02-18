#ifndef LED_H
#define LED_H

class LED {
  private:
    bool on;
  public:
    LED();
    enum class LED_STATE {
      OFF,
      ON
    };
    void setState(LED_STATE);
    void toggleState();
    bool isOn() const;
};

#endif
