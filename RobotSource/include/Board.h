#ifndef BOARD_H
#define BOARD_H

#include "Token.h"
#include <vector>

class Board {
  private:
    double length, width;
    const int NUM_COLORS, NUM_HOLES;
    Coord SQUARES[NUM_COLORS], HOLES[NUM_HOLES];
  public:
    std::vector<Token> tokens;
    Board();
    Board(double, double);
    Board(double, double, const Coord*, int, const Coord*, int);
    double getLength() const;
    double getWidth() const;
    void checkTokens() const; //Print token locations and check for correct placement
    void clear(); //Remove all tokens from board
};

#endif
