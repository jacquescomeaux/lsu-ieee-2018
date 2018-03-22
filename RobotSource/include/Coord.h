#ifndef COORD_H
#define COORD_H

class Coord {
  public:
    float x;
    float y;
    Coord(float, float);
    float dist(Coord) const; //distance between this coord and another coord
};

#endif//COORD_H
