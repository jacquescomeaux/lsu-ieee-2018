#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS[2];
Adafruit_DCMotor* motors[4]; 

void setup() {
  AFMS[0] = Adafruit_MotorShield(0x61);
  AFMS[1] = Adafruit_MotorShield(0x62);
  for(int i = 0; i < 4; i++) motors[i] = AFMS[i/2].getMotor((i%2)+1);
  for(auto a : AFMS) a.begin();
  for(auto m : motors) {
    m->setSpeed(55);
    m->run(FORWARD);
    delay(2000);
    m->run(RELEASE);
  }
}

void loop() {}
