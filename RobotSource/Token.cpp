#include "Token.h"

Token::Token() {}
Token::Token(color_opt c) : color(c), onBot(false) {}
Token::Token(Coord l, color_opt c) : location(l), color(c), onBot(false) {}

void Token::setLocation(Coord l) {
  this->location = l;
}

Coord Token::getLocation() const {
  return this->location;
}

void Token::setColor(color_opt c) {
  this->color = c;
}

color_opt Token::getColor() const {
  return this->color;
}
