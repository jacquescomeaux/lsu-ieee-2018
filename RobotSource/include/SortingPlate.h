#ifndef SORTINGPLATE_H
#define SORTINGPLATE_H

#include "SerialLink.h"

class SortingPlate : private SerialLink {
  private:
    float position;
  public:
    SortingPlate();
    void reset();
    void moveToPosition(float);
    float getPosition() const;
};

#endif
