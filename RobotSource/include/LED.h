#ifndef LED_H
#define LED_H

class LED {
  private:
    bool on;
  public:
    LED();
    void setState(/*LEDSTATE*/);
    void isOn();
};

#endif
