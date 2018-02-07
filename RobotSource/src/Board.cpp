#include "../include/Board.h"

#include <iostream>
#include <random>
#include <cmath>

Board::Board() {}

Board::Board(double l, double w) : length(l), width(w) {}

double Board::getLength() const {
  return length;
}

double Board::getWidth() const {
  return width;
}

void Board::populate(int round) { 
  if(!tokens.empty()) return;
  for(int i = 0; i < NUM_COLORS-1; i++) for(int j = 0; j < round+1 && j < 3; j++) tokens.push_back(Token(static_cast<color_opt>(i)));
  if(round == 3) for(int i = 0; i < 6; i++) tokens.push_back(Token(GRAY));
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(std::begin(tokens), std::end(tokens), g);
  for(int i = 0; i < tokens.size(); i++) if(tokens[i].getColor() == static_cast<color_opt>(i%6)) {
    int s = 0;
    while(tokens[s].getColor() == tokens[i].getColor()) s++;
    std::iter_swap(tokens.begin()+s, tokens.begin()+i);
    tokens[i].setLocation(HOLES[i/6][i%6]);
  }
  for(int i = 0; i < tokens.size(); i++) tokens[i].setLocation(HOLES[i/6][i%6]);
}

void Board::populate(const std::vector<Token>& t) {
  tokens = t;
}

void Board::populate(const std::vector<Token>& t, int r) {
  tokens = t;
  for(int i = 0; i < 6*(r+1); i++) tokens[i].setLocation(HOLES[i/6][i%6]);
}

void Board::checkTokens() const {
  if(tokens.empty()) return;
  for(int i = 0; i < tokens.size(); i++) {
    double x = tokens[i].getLocation().x;
    double y = tokens[i].getLocation().y;
    color_opt c = tokens[i].getColor();
    std::string s;
    switch(c) {
      case RED : s = "Red";
        break;
      case GREEN : s = "Green";
        break;
      case BLUE : s = "Blue";
        break;
      case CYAN : s = "Cyan";
        break;
      case MAGENTA : s = "Magenta";
        break;
      case YELLOW : s = "Yellow";
        break;
      case GRAY : s = "Gray";
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
