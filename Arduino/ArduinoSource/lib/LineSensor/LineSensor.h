#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>
//#include <Arduino.h>
#include <Fixed.h>
#include <Direction.h>
#include <ArduinoSTL.h>
#include <vector>


class LineSensor {
  private:
    const int NUM_PINS;
    const Fixed OFFSET_TO_RAD;
    unsigned char pins[32];
    QTRSensorsRC qtrrc1, qtrrc2;
    unsigned int sensor_values[32];
    Fixed SINES[32], COSINES[32];
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
