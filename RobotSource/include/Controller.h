#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Coord.h"
#include "Token.h"
#include "Robot.h"

const Coord START(-3.5, 0);
const Coord END(-3.5, 0);
const int DROP_PATH[NUM_COLORS] = {5, 4, 3, 0, 1, 2, 6};
const int COLLECT_PATH[NUM_RINGS*(NUM_COLORS-1)][2] = {
  {3,2},{1,2},{2,2},{0,2},
  {0,1},{2,1},{1,1},{3,1},
  {3,0},{1,0},{2,0},{0,0},
  {0,3},{2,3},{1,3},{3,3},
  {3,4},{1,4},{2,4},{0,4},
  {0,5},{2,5},{1,5},{3,5}
};

class Controller {
  private:
    const Robot* const robot;
  public:
    Controller(Robot*);
    runAlgorithm() const;
};

#endif
