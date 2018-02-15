#ifndef CAMERA_H
#define CAMERA_H

//#include "Intersection.h"

#include <string>

class Camera {
  private:
    std::string name;
  public:
    Camera();
    Camera(std::string name);
    std::string getName();
    bool onLine();
    bool getIntersection();
};

#endif
