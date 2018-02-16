#ifndef CAMERA_H
#define CAMERA_H

#include <string>

class Camera {
  private:
    std::string name;
  public:
    Camera();
    Camera(std::string name);
    std::string getName() const;
    bool onLine() const;
    bool getIntersection() const;
};

#endif
