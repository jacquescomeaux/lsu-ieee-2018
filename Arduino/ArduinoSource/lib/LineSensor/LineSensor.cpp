#include <LineSensor.h>

#include <Arduino.h>

LineSensor::LineSensor(unsigned char* p) :
  pins {p[0], p[1], p[2]},
  qtrrc(pins, 3),
  sensorValues {0, 0, 0} {} 

LineSensor::LineSensor(unsigned char p1, unsigned char p2, unsigned char p3) :
  pins {p1, p2, p3},
  qtrrc(pins, 3),
  sensorValues {0, 0, 0} {} 

void LineSensor::calibrateSensors() {
  //int i;
  //for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  //{
    qtrrc.calibrate();
    //delay(20);
  //
}

int LineSensor::getLineError() {
  //qtrrc.readCalibrated(sensorValues);
  return qtrrc.readLine(sensorValues) - 1000;
}

void LineSensor::printReadings() const {
  qtrrc.readCalibrated(sensorValues);
  Serial.print("left=");
  Serial.println(sensorValues[0]);
  Serial.print("middle=");
  Serial.println(sensorValues[1]);
  Serial.print("right=");
  Serial.println(sensorValues[2]);
}
