#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>

class LineSensor {
  private:
    const float KP;
    const int KD;
    QTRSensorsRC qtrrc;
    unsigned int sensorValues[3];
  public:
    void calibrateSensors();
    LineSensor(unsigned char);
};

#endif
