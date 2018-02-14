#include "LineSensor.h"

LineSensor::calibrateSensors() {
  int i;
  for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  {
    qtrrc.calibrate(QTR_NO_EMITTER_PIN);
    delay(20);
  }
}

LineSensor::LineSensor(int, int, int, ) {
 
}
