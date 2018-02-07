#include "../include/Token.h"

Token::Token() {}
Token::Token(Color c) : bottom_color(c), onBot(false) {}
Token::Token(Coord l, Color c) : location(l), bottom_color(c), onBot(false) {}

void Token::setLocation(Coord l) {
  this->location = l;
}

Coord Token::getLocation() const {
  return this->location;
}

void Token::setColor(Color c) {
  this->color = c;
}

Color Token::getColor() const {
  return this->color;
}
