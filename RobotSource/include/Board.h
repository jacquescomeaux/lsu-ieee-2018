#ifndef BOARD_H
#define BOARD_H

#include "Token.h"
#include "Coord.h"

#include <vector>
#include <list>
#include <tuple>

class Board {
  private:
    const double LENGTH, WIDTH;
    const int NUM_COLORS, NUM_HOLES;
    const std::vector<Coord> SQUARES, HOLES;
    const Coord START, END;
    const std::vector<std::list<std::pair<int,double> > > LINES;
  public:
    std::vector<Token> tokens;
    Board(double, double, const std::vector<Coord>&, const std::vector<Coord>&, Coord, Coord, const std::vector<std::list<std::pair<int,double> > >&);
    double getLength() const;
    double getWidth() const;
    Coord getStart() const;
    Coord getEnd() const;
    Coord getIntersectionLocation(int) const;
    bool getShortestPath(std::vector<int>*, int, int);
    void checkTokens() const; //Print token locations and check for correct placement
    void clear(); //Remove all tokens from board
};

#endif//BOARD_H
