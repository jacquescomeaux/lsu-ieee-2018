#include <Wheel.h>
#include <ProximitySensor.h>
#include <LineSensor.h>
#include <SortingSystem.h>

Wheel wheels[4];
ProximitySensor edge_detectors[4];
LineSensor line_sensors[8];
SortingSystem sorter;

void setup() {
  //for(int i = 0; i < 4; i++) wheels[i] = Wheel();
  //for(int i = 0; i < 4; i++) edge_detectors[i] = ProximitySensor();
  //for(int i = 0; i < 8; i++) line_sensors[i] = LineSensor();
}

void loop() {
  for(int i; i < 4; i++) if(edge_sensor[i].edgeDetected()) doSomething(i);
  if(Serial.available()) parseCommand();
  approachSpeed();
}
