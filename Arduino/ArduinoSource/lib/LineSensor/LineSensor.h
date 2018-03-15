#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTRSensors.h>

#include <Fixed.h>
#include <Direction.h>

class LineSensor {
  private:
    const int NUM_PINS;
    const unsigned int line_threshold;
    const Fixed OFFSET_TO_RAD;
    unsigned char pins[32];
    QTRSensorsRC qtrrc1, qtrrc2;
    unsigned int sensor_values[32];
    Fixed SINES[32], COSINES[32];
    void readSensors();
    Fixed getLinePosition(int offset, int range);
  public:
    LineSensor();
    void calibrateSensors();
    void getLineErrors(Fixed* x, Fixed* y, Fixed* rot, Direction);
    void getLineErrors(Fixed* x, Fixed* y, Fixed* rot, int);
    void getIntersectionErrors(Fixed* x, Fixed* y, Fixed* rot, int);
    int countLinePeaks(int range);
    void printReadings();
};

#endif//LINESENSOR_H
