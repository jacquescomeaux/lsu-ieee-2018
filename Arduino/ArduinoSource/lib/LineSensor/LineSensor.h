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
    LineSensor(unsigned char);
    void calibrateSensors();
    int getLineError();
};

#endif
