#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>
//#include <Arduino.h>
#include <Fixed.h>

class LineSensor {
  private:
    const int NUM_PINS;
    unsigned char pins[NUM_PINS];
    QTRSensorsRC qtrrc;
    unsigned int sensor_values[NUM_PINS];
    Fixed SINES[NUM_PINS], COSINES[NUM_PINS];
    Fixed getLinePosition(int offset, int range);
  public:
    LineSensor(unsigned char);
    //LineSensor(unsigned char, unsigned char, unsigned char);
    void calibrateSensors();
    void getLineErrors(Fixed* x, Fixed* y, Fixed* rot, Direction);
    void getLineErrors(Fixed* x, Fixed* y, Fixed* rot, int);
    void printReadings();
};

#endif//LINESENSOR_H
