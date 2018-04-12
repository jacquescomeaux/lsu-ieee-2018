#ifndef COORD_H
#define COORD_H

class Coord {
  public:
    double x;
    double y;
    Coord(double, double);
    double dist(Coord) const; //distance between this coord and another coord
};

#endif//COORD_H
