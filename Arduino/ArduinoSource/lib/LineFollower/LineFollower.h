#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include <Fixed.h>
#include <Flag.h>

#include <LineSensor.h>

class LineFollower {
  private:
    Fixed pid_terms[3][5];
    bool array_filled; 
    LineSensor line_sensor;
  protected:
    LineFollower();
  public:
    void calibrateSensors();
    void correctErrors(Fixed, Fixed, Fixed, Fixed*, Fixed*, Fixed*);
    void getLineCorrections(Fixed*, Fixed*, Fixed*, unsigned int offset, unsigned int range);
    void adjustPID(unsigned int var, unsigned int term, Fixed);
    void resetPIDData();
};

#endif//LINEFOLLOWER_H
