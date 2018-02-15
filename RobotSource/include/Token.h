#ifndef TOKEN_H
#define TOKEN_H

#include "Coord.h"
#include "Color.h"

class Token {
  private:
    Coord location;
    Color bottom_color;
  public:
    Token();
    Token(Color);
    Token(Coord, Color);
    bool onBot; //whether or not token is currently on a robot; location is meaningless if true
    void setLocation(Coord);
    Coord getLocation() const;
    void setColor(Color);
    Color getColor() const;
};

#endif
