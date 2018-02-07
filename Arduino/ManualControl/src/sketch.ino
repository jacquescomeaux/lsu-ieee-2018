#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS;
Adafruit_DCMotor* motors[4]; 
int a;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  AFMS = Adafruit_MotorShield(0x61);
  for(int i = 0; i < 4; i++) motors[i] = AFMS.getMotor(i+1);
  AFMS.begin();  // create with the default frequency 1.6KHz
  for(int i = 0; i < 4; i++) motors[i]->setSpeed(55);
  for(int i = 0; i < 4; i++) motors[i]->run(RELEASE);
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  a = 0;
}

void loop() {
  if(Serial.available()) {
    if(++a%2) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);
    unsigned char byte_received = Serial.read();
    switch(byte_received) {
      case 'w':
        for(int i = 0; i < 4; i++) motors[i]->run(FORWARD);
        break;
      case 'a':
        for(int i = 0; i < 4; i++) motors[i]->run((i%2)?FORWARD:BACKWARD);
        break;
      case 's':
        for(int i = 0; i < 4; i++) motors[i]->run(BACKWARD);
        break;
      case 'd':
        for(int i = 0; i < 4; i++) motors[i]->run(!(i%2)?FORWARD:BACKWARD);
        break;
      case '1':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(50);
        break;
      case '2':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(100);;
        break;
      case '3':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(150);
        break;
      case '4':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(200);
        break;
      case '5':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(250);
        break;
      default:
        for(int i = 0; i < 4; i++) motors[i]->run(RELEASE);
    }
  }
}
