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
    Fixed getLinePosition(int offset, int range, bool along_arc);
  public:
    LineSensor();
    void calibrateSensors();
    void getLineErrors(Fixed* x, Fixed* y, Fixed* rot, Direction, int);
    void getLineErrors(Fixed* x, Fixed* y, Fixed* rot, int, int);
    void getCrossIntersectionErrors(Fixed* x, Fixed* y, Fixed* rot, int);
    void getCornerIntersectionErrors(Fixed* x, Fixed* y, Fixed* rot, int);
    void precalibrate(int, int);
    int countLinePeaks(int range);
    void printReadings();
    void printLinePeaks();
    void printCalibratedValues();
    void printErrors(Fixed, Fixed, Fixed);
};

#endif//LINESENSOR_H
