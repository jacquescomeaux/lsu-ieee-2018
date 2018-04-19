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
};

#endif//VELOCITYVECTOR_H
