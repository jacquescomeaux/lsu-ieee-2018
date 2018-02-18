#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>
#include <Arduino.h>

class LineSensor {
  private:
    const QTRSensorsRC qtrrc;
    unsigned int sensorValues[3];
    void init() const;
  public:
    LineSensor(unsigned char);
    ///void calibrateSensors();
    int getLineError();
    void printReadings() const;
};

#endif
