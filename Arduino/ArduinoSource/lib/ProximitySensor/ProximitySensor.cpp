#include "ProximitySensor.h"
#include <Arduino.h>

ProximitySensor::ProximitySensor(int t, int e) : ProximitySensor(t, e, 600) {}

ProximitySensor::ProximitySensor(int t, int e, float c) : trig_pin(t), echo_pin(e), cutoff(c){
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  count = 0;
}

void ProximitySensor::updateProximity() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  float temp_proximity;
  temp_proximity = pulseIn(echo_pin, HIGH);
  if(temp_proximity > 400 && temp_proximity < 800) proximity = temp_proximity;
  prevProx[count++] = proximity;
  count %= 20;
}

float ProximitySensor::getProximity() {
  //updateProximity();
  return proximity;
}

float ProximitySensor::getAvgProximity() {
  float sum = 0;
  updateProximity();
  for(float f : prevProx) sum += f;
  return sum;
  //return proximity;
}

bool ProximitySensor::edgeDetected() {
  updateProximity();
  //Serial.println(proximity);
  //return proximity > cutoff;
  //return getAvgProximity() > 20 * cutoff;
  return getProximity() > cutoff;
}
