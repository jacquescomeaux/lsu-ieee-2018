#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>
//#include <Arduino.h>

class LineSensor {
  private:
    unsigned char pins[3];
    QTRSensorsRC qtrrc;
    unsigned int sensorValues[3];
  public:
    LineSensor(unsigned char*);
    LineSensor(unsigned char, unsigned char, unsigned char);
    ///void calibrateSensors();
    int getLineError();
    void printReadings() const;
};

#endif//LINESENSOR_H
