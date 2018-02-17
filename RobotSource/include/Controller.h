#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Direction.h"

#include <vector> 

class Robot;

class Controller {
  private:
    Robot& robot;
    const int NUM_LINES;
    const std::vector<Direction> follow_sequence, cover_sequence;
    //void init(Direction*, Direction*, int)
    void coverLine(Direction, int) const;
  public:
    Controller(Robot&);
    Controller(Robot&, Direction*, Direction*, int);
    void runAlgorithm() const;
};

#endif
