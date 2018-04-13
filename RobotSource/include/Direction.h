#ifndef DIRECTION_H
#define DIRECTION_H

//#include <stdint.h>

class Direction {
  private:
    double computeX() const;
    double computeY() const;
    double computeRot() const;
    double computeOmega() const;
    double computeTheta() const;
    int computeOffset(double) const;
  public:
    const double x, y, rot;
    const double theta, omega;
    const int offset;
    Direction(double, double);
    Direction(double, double, double);
};


/*enum class Direction : uint8_t {
  NONE = 0,
  FRONT = 1,
  BACK = 2,
  LEFT = 3,
  RIGHT = 4,
  FRONT_LEFT = 5,
  FRONT_RIGHT = 6,
  BACK_LEFT = 7,
  BACK_RIGHT = 8,
  CLOCKWISE = 9,
  COUNTER_CLOCKWISE = 10
};*/

#endif
