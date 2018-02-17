#include "../include/Board.h"

#include <iostream>
#include <cmath>

Board::Board() : Board(8, 8) {}

Board::Board(float l, float w) :
  length(l),
  width(w),
  NUM_HOLES(24),
  NUM_COLORS(7),
  SQUARES {
    Coord(-3.5f,  3.5f),     //Red
    Coord(-3.5f,  0.0f),     //Green
    Coord(-3.5f, -3.5f),     //Blue
    Coord( 3.5f,  3.5f),     //Cyan
    Coord( 3.5f,  0.0f),     //Magenta
    Coord( 3.5f, -3.5f),     //Yellow
    Coord( 0.0f,  0.0f)      //Gray
  },
  HOLES {
    Coord(-1.0f,  1.0f),
    Coord(-1.0f,  0.0f),
    Coord(-1.0f, -1.0f),
  
    Coord( 1.0f,  1.0f),
    Coord( 1.0f,  0.0f),
    Coord( 1.0f, -1.0f),
  
    Coord(-2.0f,  2.0f),
    Coord(-2.0f,  0.0f),
    Coord(-2.0f, -2.0f),
  
    Coord( 2.0f,  2.0f),
    Coord( 2.0f,  0.0f),
    Coord( 2.0f, -2.0f),
  
    Coord(-1.5f,  1.5f),
    Coord(-1.5f,  0.0f),
    Coord(-1.5f, -1.5f),
  
    Coord( 1.5f,  1.5f),
    Coord( 1.5f,  0.0f),
    Coord( 1.5f, -1.5f),
  
    Coord(-2.5f,  2.5f),
    Coord(-2.5f,  0.0f),
    Coord(-2.5f, -2.5f),
  
    Coord( 2.5f,  2.5f),
    Coord( 2.5f,  0.0f),
    Coord( 2.5f, -2.5f)
  },
  START(-3.5, 0),
  END(-3.5, 0) {}

Board::Board(float l, float w, const Coord* squares, int s, const Coord* holes, int h, Coord start, Coord end) : length(l), width(w), NUM_COLORS(s), NUM_HOLES(s), SQUARES(squares, squares + s), HOLES(holes, holes + h), START(start), END(end) {
  //for(int i = 0; i < s; i++) SQUARES[i] = squares[i];
  //for(int i = 0; i < h; i++) HOLES[i] = holes[i];
}

float Board::getLength() const {
  return length;
}

float Board::getWidth() const {
  return width;
}
Coord Board::getStart() const {
  return START;
}

Coord Board::getEnd() const {
  return END;
}

void Board::checkTokens() const {
  if(tokens.empty()) return;
  for(int i = 0; i < tokens.size(); i++) {
    float x = tokens[i].getLocation().x;
    float y = tokens[i].getLocation().y;
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
