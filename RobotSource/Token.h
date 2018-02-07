#ifndef TOKEN_H
#define TOKEN_H

#include "Coord.h"

typedef enum {RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, GRAY} color_opt;

class Token {
  private:
    Coord location;
    color_opt color;
  public:
    Token();
    Token(color_opt);
    Token(Coord, color_opt);
    bool onBot; //whether or not token is currently on a robot; location is meaningless if true
    void setLocation(Coord);
    Coord getLocation() const;
    void setColor(color_opt);
    color_opt getColor() const;
};

#endif
