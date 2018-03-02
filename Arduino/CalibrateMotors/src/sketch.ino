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
  for(int i = 0; i < 4; i++) {
    motors[i]->setSpeed(55);
    motors[i]->run(FORWARD);
    delay(2000);
    motors[i]->run(RELEASE);
  }
}

void loop() {}
