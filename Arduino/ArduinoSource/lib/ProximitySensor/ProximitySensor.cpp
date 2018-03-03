#include "ProximitySensor.h"
#include <Arduino.h>

ProximitySensor::ProximitySensor(int t, int e) : ProximitySensor(t, e, 600) {}

ProximitySensor::ProximitySensor(int t, int e, float c) : trig_pin(t), echo_pin(e), cutoff(c){
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void ProximitySensor::updateProximity() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  proximity = pulseIn(echo_pin, HIGH);
}

float ProximitySensor::getProximity() {
  updateProximity();
  return proximity;
}

bool ProximitySensor::edgeDetected() {
  updateProximity();
  //Serial.println(proximity);
  return proximity > cutoff;
}
