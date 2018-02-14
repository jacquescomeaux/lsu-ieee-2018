#include "LineSensor.h"

void LineSensor::calibrateSensors() {
  int i;
  for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  {
    qtrrc.calibrate(QTR_NO_EMITTER_PIN);
    //delay(20);
  }
}

LineSensor::LineSensor(unsigned char pin) : KP(0.2f), KD(5), qtrrc() {
  unsigned char pins[3] = {pin, pin + 1, pin + 2};
  qtrrc.init(pins, 3);
}
