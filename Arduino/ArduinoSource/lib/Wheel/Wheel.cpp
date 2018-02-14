#include "Wheel.h"

Wheel::Wheel() {
  for(int i = 0; i < 2; i++) this->AFMS[i] = Adafruit_MotorShield(0x60 + i);
  for(int i = 0; i < 4; i++ ) this->motors[i] = AFMS[i/2].getMotor((i%2)+1); 
 

}
