#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>

class LineSensor {
  private:
    QTRSensorsRC qtrrc;
    unsigned int sensorValues[3];
  public:
    LineSensor(unsigned char);
    void calibrateSensors();
    int getLineError();
};

#endif
