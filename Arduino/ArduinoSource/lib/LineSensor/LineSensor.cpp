#include <LineSensor.h>

LineSensor::LineSensor(unsigned char pin) :
  pins {pin, pin + 1, pin + 2},
  qtrrc(pins, 3),
  sensorValues {0, 0, 0} {} 

/*void LineSensor::calibrateSensors() {
  int i;
  for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  {
    qtrrc.calibrate(QTR_NO_EMITTER_PIN);
    //delay(20);
  }
}*/

int LineSensor::getLineError() {
  qtrrc.read(sensorValues);
  return qtrrc.readLine(sensorValues) - 1000;
}

void LineSensor::printReadings() const {
  Serial.print("left=");
  Serial.println(sensorValues[0]);
  Serial.print("middle=");
  Serial.println(sensorValues[1]);
  Serial.print("right=");
  Serial.println(sensorValues[2]);
}
