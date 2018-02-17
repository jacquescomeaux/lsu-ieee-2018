#ifndef BOARD_H
#define BOARD_H

#include "Token.h"

#include <vector>

class Board {
  private:
    const float length, width;
    const int NUM_COLORS, NUM_HOLES;
    const std::vector<Coord> SQUARES, HOLES;
    const Coord START, END;
  public:
    std::vector<Token> tokens;
    Board();
    Board(float, float);
    Board(float, float, const Coord*, int, const Coord*, int);
    float getLength() const;
    float getWidth() const;
    Coord getStart() const;
    Coord getEnd() const;
    void checkTokens() const; //Print token locations and check for correct placement
    void clear(); //Remove all tokens from board
};

#endif
