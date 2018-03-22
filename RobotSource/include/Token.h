#ifndef TOKEN_H
#define TOKEN_H

#include "Color.h"
#include "Coord.h"

class Token {
  private:
    const Color bottom_color;
    Coord* location;
    bool external_location;
  public:
    Token(Color);
    Token(Color, Coord);
    Token(Color, Coord*);
    ~Token();
    void setLocation(Coord);
    void setLocation(Coord*);
    Coord getLocation() const;
    Color getColor() const;
};

#endif//TOKEN_H
