#ifndef VELOCITYVECTOR_H
#define VELOCITYVECTOR_H

class VelocityVector {
  private:
    const double RAD_TO_OFFSET;
    double computeAngle(double, double) const;
    double computeMagnitude(double, double) const;
    unsigned int computeOffset(double) const;
  public:
    const double x, y, angle, magnitude, rot;
    const unsigned int offset;
    VelocityVector(double x, double y, double rot);
    VelocityVector& operator+=(const VelocityVector&);
    VelocityVector& operator-=(const VelocityVector&);
    VelocityVector& operator*=(double);
    VelocityVector& operator/=(double);
};

inline bool operator==(const VelocityVector&, const VelocityVector&);
inline bool operator!=(const VelocityVector&, const VelocityVector&);
inline VelocityVector operator+(VelocityVector, const VelocityVector&);
inline VelocityVector operator-(VelocityVector, const VelocityVector&);
inline VelocityVector operator*(double, VelocityVector);
inline VelocityVector operator*(VelocityVector,  double);
inline VelocityVector operator/(VelocityVector, double);

inline bool operator==(const VelocityVector& lhs, const VelocityVector& rhs) {
  return(lhs.x == rhs.x && lhs.y == rhs.y && lhs.rot == rhs.rot);
}

inline bool operator!=(const VelocityVector& lhs, const VelocityVector& rhs) {
  return !operator==(lhs,rhs);
}

inline VelocityVector operator+(VelocityVector lhs, const VelocityVector& rhs) {
  VelocityVector result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.rot + rhs.rot);
  return result;
}

inline VelocityVector operator-(VelocityVector lhs, const VelocityVector& rhs) {
  VelocityVector result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.rot - rhs.rot);
  return result;
}

inline VelocityVector operator*(VelocityVector lhs, double rhs) {
  VelocityVector result(lhs.x * rhs, lhs.y * rhs, lhs.rot * rhs);
  return result;
}

inline VelocityVector operator*(double lhs, VelocityVector rhs) {
  VelocityVector result(lhs * rhs.x, lhs * rhs.y, lhs * rhs.rot);
  return result;
}

inline VelocityVector operator/(VelocityVector lhs, double rhs) {
  VelocityVector result(lhs.x / rhs, lhs.y / rhs, lhs.rot / rhs);
  return result;
}

#endif//VELOCITYVECTOR_H
