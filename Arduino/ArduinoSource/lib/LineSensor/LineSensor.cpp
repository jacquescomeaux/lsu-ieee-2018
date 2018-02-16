#include <LineSensor.h>

LineSensor::LineSensor(unsigned char pin) : qtrrc(), sensorValues {0,0,0} {
  unsigned char pins[3] = {pin, pin + 1, pin + 2};
  qtrrc.init(pins, 3);
}

void LineSensor::calibrateSensors() {
  int i;
  for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  {
    qtrrc.calibrate(QTR_NO_EMITTER_PIN);
    //delay(20);
  }
}

int LineSensor::getLineError() {
  qtrrc.read(sensorValues);
  Serial.println("running get line error");
  return qtrrc.readLine(sensorValues) - 1000;
}

void LineSensor::printReadings() {
  Serial.print("left=");
  Serial.println(sensorValues[0]);
  Serial.print("middle=");
  Serial.println(sensorValues[1]);
  Serial.print("right=");
  Serial.println(sensorValues[2]);
}
