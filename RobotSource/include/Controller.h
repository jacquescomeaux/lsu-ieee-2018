#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Direction.h"
#include <vector> 

class SortBot;

class Controller {
  private:
    SortBot& robot;
    const int NUM_LINES;
    const std::vector<Direction> follow_sequence, cover_sequence;
    //void init(Direction*, Direction*, int)
    void coverLine(Direction, int) const;
  public:
    Controller(SortBot&);
    Controller(SortBot&, Direction*, Direction*, int);
    void runAlgorithm() const;
};

#endif
