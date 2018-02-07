#ifndef CAMERA_H
#define CAMERA_H

#include <string>

class Camera {
  private:
    std::string name;
  public:
    Camera(std::string name);
    std::string getName();
};

#endif
