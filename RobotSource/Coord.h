#ifndef COORD_H
#define COORD_H

class Coord {
  public:
    float x;
    float y;
    Coord();
    Coord(float, float);
    float dist(Coord); //distance between this coord and another coord
};

#endif
