#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>

class LineSensor {
  private:
    const float KP;
    const int KD;
    QTRSensors qtrrc;
    unsigned int sensorValues[3];
  public:
    LineSensor(int pin) : KP(0.2f), KD(5), TIMEOUT(2500) QTRSensors((unsigned char[]) {pin, pin+1, pin+2}, 3, TIMEOUT, QTR_NO_EMITTER_PIN);
};

#endif
