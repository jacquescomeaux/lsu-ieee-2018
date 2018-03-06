#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>


Adafruit_MotorShield AFMS[2];
Adafruit_DCMotor* motors[4];
Encoder encoders[4]; 

void setup() {
  AFMS[0] = Adafruit_MotorShield(0x61);
  AFMS[1] = Adafruit_MotorShield(0x62);
  encoders[0] = enc(2, 4); //define encoders
  encoders[1] = enc(3, 5)
  encoders[2] = enc(18, 22);
  encoders[3] = enc(19, 23);
  
  for(int i = 0; i < 4; i++) motors[i] = AFMS[i/2].getMotor((i%2)+1);
  for(auto a : AFMS) a.begin();
  for(int i = 0; i < 4; i++) {
	Serial.println("Motor 0:");
	Serial.print("Start Position: ");
	Serial.println(encoders[i].read());
    motors[i]->setSpeed(55);
    motors[i]->run(FORWARD);
    delay(2000);
	Serial.print("End Position: ");
	Serial.println(encoders[i].read());
    motors[i]->run(RELEASE);
  }
}

void loop() {}
