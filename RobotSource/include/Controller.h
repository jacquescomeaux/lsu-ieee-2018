#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SerialLink.h"

#include "Direction.h"
#include <vector> 
#include "Color.h"

class SortBot;

class Controller : private SerialLink {
  private:
    SortBot& robot;
    const int NUM_LINES;
    const std::vector<Direction> follow_sequence, cover_sequence;
    const std::vector<bool> type_sequence;
    const std::vector<int> offset_sequence;
    const std::vector<float> dist_sequence;
    const std::vector<float> travel_sequence;
    //void init(Direction*, Direction*, int)
    void coverLine(Direction, bool, int, int) const;
    void waitForEnter() const;
  public:
    Controller(SortBot&);
    Controller(SortBot&, Direction*, Direction*, int);
    void runAlgorithm() const;
};

#endif//CONTROLLER_H
