#ifndef BOARD_H
#define BOARD_H

#include "Token.h"
#include <vector>

const int NUM_RINGS = 4;
const int NUM_COLORS = 7;

//Locations of colored squares
const Coord SQUARES[NUM_COLORS] = {
  Coord(-3.5, 3.5), //Red
  Coord(-3.5, 0),   //Green
  Coord(-3.5, -3.5),//Blue
  Coord(3.5, 3.5),  //Cyan
  Coord(3.5, 0),    //Magenta
  Coord(3.5, -3.5), //Yellow
  Coord(0, 0),      //Gray
};
//Locations of token depressions
const Coord HOLES[NUM_RINGS][NUM_COLORS-1] = {
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
};
class Board {
  private:
    double length;
    double width;
  public:
    std::vector<Token> tokens;
    Board();
    Board(double, double);
    double getLength() const;
    double getWidth() const;
    /*void populate(int); //Generate a random token arrangement per round specifications
    void populate(const std::vector<Token>&); //Load a premade list of tokens onto the board
    void populate(const std::vector<Token>&, int); //Load a premade list of tokens into the token depressions
    */
    void checkTokens() const; //Print token locations and check for correct placement
    void clear(); //Remove all tokens from board
};

#endif
