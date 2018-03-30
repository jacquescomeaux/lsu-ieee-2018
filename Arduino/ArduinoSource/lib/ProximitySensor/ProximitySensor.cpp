#include "ProximitySensor.h"
#include <Arduino.h>

ProximitySensor::ProximitySensor(int t, int e) :
  range_min(600),
  range_max(800),
  certainty_threshold(1),
  trig_pin(t),
  echo_pin(e),
  proximity(500),
  count(0)
  {
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
  
  /*Serial.print("T: ");
  Serial.print(millis());
  Serial.print(" P: ");
  Serial.print(proximity);*/

if(proximity > range_min && proximity < range_max) count++;
  else count = 0;
}

bool ProximitySensor::edgeDetected() {
  updateProximity();
  return count > certainty_threshold;
}
