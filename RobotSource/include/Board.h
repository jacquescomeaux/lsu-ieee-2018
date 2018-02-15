#ifndef BOARD_H
#define BOARD_H

#include "Token.h"
#include <vector>

//Locations of colored squares
/*const Coord SQUARES[NUM_COLORS] = {
  Coord(-3.5, 3.5), //Red
  Coord(-3.5, 0),   //Green
  Coord(-3.5, -3.5),//Blue
  Coord(3.5, 3.5),  //Cyan
  Coord(3.5, 0),    //Magenta
  Coord(3.5, -3.5), //Yellow
  Coord(0, 0),      //Gray
};*/
//Locations of token depressions
/*const Coord HOLES[NUM_RINGS][NUM_COLORS-1] = {
  {Coord(-1,1), Coord(-1,0), Coord(-1,-1),
   Coord(1, 1), Coord(1, 0), Coord(1, -1)
  },
  {Coord(-2,2), Coord(-2,0), Coord(-2,-2),
   Coord(2, 2), Coord(2, 0), Coord(2, -2)
  },
  {Coord(-1.5,1.5), Coord(-1.5,0), Coord(-1.5,-1.5),
   Coord(1.5, 1.5), Coord(1.5, 0), Coord(1.5, -1.5)
  },
  {Coord(-2.5,2.5), Coord(-2.5,0), Coord(-2.5,-2.5),
   Coord(2.5, 2.5), Coord(2.5, 0), Coord(2.5, -2.5)
  },
};*/
class Board {
  private:
    double length, width;
    const int NUM_HOLES, NUM_COLORS;
    //Coord SQUARES[NUM_COLORS];
    //Coord HOLES[NUM_HOLES];
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
