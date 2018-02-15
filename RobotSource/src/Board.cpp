#include "../include/Board.h"

#include <iostream>
#include <cmath>

Board::Board() : Board(8, 8) {}

Board::Board(double l, double w) : length(l), width(w), NUM_HOLES(24), NUM_COLORS(7) {
  SQUARES[0] = Coord(-3.5f,  3.5f);     //Red
  SQUARES[1] = Coord(-3.5f,  0.0f);     //Green
  SQUARES[2] = Coord(-3.5f, -3.5f);     //Blue
  SQUARES[3] = Coord( 3.5f,  3.5f);     //Cyan
  SQUARES[4] = Coord( 3.5f,  0.0f);     //Magenta
  SQUARES[5] = Coord( 3.5f, -3.5f);     //Yellow
  SQUARES[6] = Coord( 0.0f,  0.0f);     //Gray
  //Locations of token depressions
  HOLES[ 0] = Coord(-1.0f,  1.0f);
  HOLES[ 1] = Coord(-1.0f,  0.0f);
  HOLES[ 2] = Coord(-1.0f, -1.0f);
  HOLES[ 3] = Coord( 1.0f,  1.0f);
  HOLES[ 4] = Coord( 1.0f,  0.0f);
  HOLES[ 5] = Coord( 1.0f, -1.0f);
  HOLES[ 6] = Coord(-2.0f,  2.0f);
  HOLES[ 7] = Coord(-2.0f,  0.5f);
  HOLES[ 8] = Coord(-2.0f, -0.0f);
  HOLES[ 9] = Coord( 2.0f, -3.5f);
  HOLES[10] = Coord( 2.0f,  3.5f);
  HOLES[11] = Coord( 2.0f,  0.0f);
  HOLES[12] = Coord(-1.5f, -3.5f);
  HOLES[13] = Coord(-1.5f,  0.0f);
  HOLES[14] = Coord(-1.5f,  3.5f);
  HOLES[15] = Coord( 1.5f,  0.0f);
  HOLES[16] = Coord( 1.5f, -3.5f);
  HOLES[17] = Coord( 1.5f,  3.5f);
  HOLES[18] = Coord(-2.5f,  0.0f);
  HOLES[19] = Coord(-2.5f, -3.5f);
  HOLES[20] = Coord(-2.5f,  0.0f);
  HOLES[21] = Coord( 2.5f,  3.5f);
  HOLES[22] = Coord( 2.5f,  0.0f);
  HOLES[23] = Coord( 2.5f, -3.5f);
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
}

Board::Board(double l, double w, const Coord* squares, int s, const Coord* holes, int h) : length(l), width(w) {

}

double Board::getLength() const {
  return length;
}

double Board::getWidth() const {
  return width;
}

void Board::checkTokens() const {
  if(tokens.empty()) return;
  for(int i = 0; i < tokens.size(); i++) {
    double x = tokens[i].getLocation().x;
    double y = tokens[i].getLocation().y;
    Color c = tokens[i].getColor();
    std::string s;
    switch(c) {
      case Color::RED : s = "Red";
        break;
      case Color::GREEN : s = "Green";
        break;
      case Color::BLUE : s = "Blue";
        break;
      case Color::CYAN : s = "Cyan";
        break;
      case Color::MAGENTA : s = "Magenta";
        break;
      case Color::YELLOW : s = "Yellow";
        break;
      case Color::GRAY : s = "Gray";
        break;
      default : s = "Error";
    }
    if((std::abs(x-SQUARES[c].x) < 0.5) && (std::abs(y-SQUARES[c].y) < 0.5)) std::cout << "Correct:   ";
    else std::cout << "Incorrect: ";
    std::cout << s << " token at location (" << x << ", " << y << ")" << std::endl;
  }
}

void Board::clear() {
  tokens.clear();
}
