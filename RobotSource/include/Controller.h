#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Direction.h"

class Robot;

class Controller {
  private:
    Robot& robot;
    static const int NUM_LINES;
    Direction follow_sequence[NUM_LINES];
    Direction cover_sequence[NUM_LINES];
    void coverLine(Direction, int) const;
  public:
    Controller(Robot&);
    Controller(Robot&, Direction*, Direction*, int);
    void runAlgorithm() const;
};

#endif
