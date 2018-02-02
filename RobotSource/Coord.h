#ifndef COORD_H
#define COORD_H

class Coord {
  public:
    double x;
    double y;
    Coord();
    Coord(double, double);
    double dist(Coord); //distance between this coord and another coord
};

#endif
