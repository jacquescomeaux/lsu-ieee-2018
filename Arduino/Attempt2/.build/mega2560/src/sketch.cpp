#include <Arduino.h>
#include <Robot.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
void accelerateTo(float speed);
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <Robot.h>
//#include <Wire.h>
//#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS[2];
Adafruit_DCMotor* motors[4]; 
const float delta = 0.1;
int currentSpeeds[4];

void accelerateTo(float speed) {
  return;
}

Robot r;


void setup() {

}

void loop() {
  if(Serial.available()) {
    
  }

}
