#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
//#include <Encoder.h>

Adafruit_MotorShield AFMS[2];
Adafruit_DCMotor* motors[4];
//Encoder* encoders[4]; 

void setup() {
  Serial.begin(9600);
  Serial.println("Waiting");
  while(!Serial.available());
  Serial.println("Continue");
  AFMS[0] = Adafruit_MotorShield(0x61);
  AFMS[1] = Adafruit_MotorShield(0x62);
  /*encoders[0] = new Encoder(2, 4); //define encoders
  encoders[1] = new Encoder(3, 5);
  encoders[2] = new Encoder(18, 20);
  encoders[3] = new Encoder(19, 21);
  */
  for(auto& a : AFMS) a.begin();
  for(int i = 0; i < 4; i++) motors[i] = AFMS[i/2].getMotor((i%2)+1);
  for(int i = 0; i < 4; i++) {
    Serial.print("Motor ");
    Serial.print(i);
    Serial.println(":");
    Serial.print("Start Position: ");
    //Serial.println(encoders[i]->read());
    motors[i]->setSpeed(55);
    motors[i]->run(FORWARD);
    delay(2000);
    Serial.print("End Position: ");
    //Serial.println(encoders[i]->read());
    motors[i]->run(RELEASE);
  }
}

void loop() {}
