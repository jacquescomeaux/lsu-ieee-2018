#ifndef SENSORRING_H
#define SENSORRING_H

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
    SensorStrip line_sensors[8];
  protected:
    SensorRing();
  public:
    bool onLine();
    bool atIntersection();
};

#endif
