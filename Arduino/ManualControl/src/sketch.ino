#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS[2];
Adafruit_DCMotor* motors[4]; 
const float delta = 0.1;
int currentSpeeds[4];

void setup() {
  AFMS[0] = Adafruit_MotorShield(0x61);
  AFMS[1] = Adafruit_MotorShield(0x62);
  for(int i = 0; i < 4; i++) motors[i] = AFMS[i/2].getMotor((i%2)+1);
  /*motors[0] = AFMS[0].getMotor(1);
  motors[1] = AFMS[0].getMotor(2);
  motors[2] = AFMS[1].getMotor(1);
  motors[3] = AFMS[1].getMotor(2);
  */
  
  for(int i = 0; i < 2; i++) AFMS[i].begin();  // create with the default frequency 1.6KHz

  for(int i = 0; i < 4; i++) motors[i]->setSpeed(55);
  for(int i = 0; i < 4; i++) currentSpeeds[i] = 55;
  
  for(int i = 0; i < 4; i++) motors[i]->run(RELEASE);
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  motors[3]->run(FORWARD);
}

void veerRight() {
  for(int i = 0; i < 2; i++) currentSpeeds[i] *= (1+delta);
  for(int i = 2; i < 4; i++) currentSpeeds[i] *= (1-delta);
  for(int i = 0; i < 4; i++) motors[i]->setSpeed(currentSpeeds[i]);
}

void veerLeft() {
  for(int i = 0; i < 2; i++) currentSpeeds[i] *= (1-delta);
  for(int i = 2; i < 4; i++) currentSpeeds[i] *= (1+delta);
  for(int i = 0; i < 4; i++) motors[i]->setSpeed(currentSpeeds[i]);
}

void loop() {
  if(Serial.available()) {
    unsigned char byte_received = Serial.read();
    switch(byte_received) {
      case 'w':
        for(int i = 0; i < 4; i++) motors[i]->run(FORWARD);
        break;
      case 'a':
        for(int i = 0; i < 4; i++) motors[i]->run(!(i%2)?FORWARD:BACKWARD);
        break;
      case 'x':
        for(int i = 0; i < 4; i++) motors[i]->run(BACKWARD);
        break;
      case 'd':
        for(int i = 0; i < 4; i++) motors[i]->run((i%2)?FORWARD:BACKWARD);
        break;
      case 'q':
        for(int i = 0; i < 4; i++) motors[i]->run(!(i%2)?FORWARD:RELEASE);
        break;
      case 'e':
        for(int i = 0; i < 4; i++) motors[i]->run((i%2)?FORWARD:RELEASE);
        break;
      case 'z':
        for(int i = 0; i < 4; i++) motors[i]->run(!(i%2)?RELEASE:BACKWARD);
        break;
      case 'c':
        for(int i = 0; i < 4; i++) motors[i]->run((i%2)?RELEASE:BACKWARD);
        break;
      case 'u':
        for(int i = 0; i < 4; i++) motors[i]->run((i/2)?FORWARD:BACKWARD);
        break;
      case 'i':
        for(int i = 0; i < 4; i++) motors[i]->run(!(i/2)?FORWARD:BACKWARD);
        break;
      case 'j':
        veerLeft();
        break;
      case 'k':
        veerRight();
        break;
      case '1':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(25);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 25;
        break;
      case '2':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(50);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 50;
        break;
      case '3':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(75);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 75;
        break;
      case '4':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(100);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 100;
        break;
      case '5':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(125);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 125;
        break;
      case '6':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(150);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 150;
        break;
      case '7':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(175);;
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 175;
        break;
      case '8':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(200);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 200;
        break;
      case '9':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(225);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 225;
        break;
      case '0':
        for(int i = 0; i < 4; i++) motors[i]->setSpeed(0);
        for(int i = 0; i < 4; i++) currentSpeeds[i] = 0;
        break;
      default:
        for(int i = 0; i < 4; i++) motors[i]->run(RELEASE);
    }
  }
}
