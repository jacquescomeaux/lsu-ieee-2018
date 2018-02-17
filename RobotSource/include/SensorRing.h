#ifndef SENSORRING_H
#define SENSORRING_H

#include "SerialLink.h"

class SensorRing : private SerialLink {
  private:
    class SensorStrip {
      public:
        SensorStrip() {}
        int getLeft() {return 0;}
        int getMiddle() {return 0;}
        int getRight() {return 0;}
        float getAdjustment() {return 0;}
        bool onLine() {return true;}
    };
    const SensorStrip line_sensors[8];
  public:
    SensorRing();
    bool onLine() const;
    bool atIntersection() const;
};

#endif
