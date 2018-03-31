#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include <Direction.h>
#include <Fixed.h>
#include <Flag.h>

#include <LineSensor.h>

class LineFollower {
  private:
    bool array_filled; 
    Fixed pid_terms[3][5];
    LineSensor line_sensor;
    unsigned int resolveOffset(Direction dir);
    void correctErrors(Fixed, Fixed, Fixed, Fixed*, Fixed*, Fixed*);
    void getLineCorrections(Fixed*, Fixed*, Fixed*, unsigned int offset, unsigned int range);
    void getCenterCorrections(Fixed*, Fixed*, Fixed*, bool cross, unsigned int offset);
  public:
    LineFollower();
    void adjustPID(unsigned int var, unsigned int term, Fixed);
};

#endif//LINEFOLLOWER_H
