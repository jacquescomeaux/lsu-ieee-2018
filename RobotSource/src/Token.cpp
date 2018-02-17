#include "../include/Token.h"

Token::Token(Color c) : Token(c, Coord(0.0f, 0.0f)) {}

Token::Token(Color c, Coord l) : bottom_color(c), location(new Coord(l)), external_location(false) {}

Token::Token(Color c, Coord* l) : bottom_color(c), location(l), external_location(true) {}
    
Token::~Token() {
  if(!external_location) delete location;
}

void Token::setLocation(Coord l) {
  if(!external_location) delete location;
  location = new Coord(l);
  external_location = false;
}

void Token::setLocation(Coord* l) {
  if(!external_location) delete location;
  location = l;
  external_location = true;
}

Coord Token::getLocation() const {
  return *location;
}

Color Token::getColor() const {
  return bottom_color;
}
