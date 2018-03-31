#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Coord.h"
#include <string>

class Camera {
  private:
    cv::VideoCapture cap;
    cv::Mat M;
    int countBlack();
  public:
    Camera(int n);
    bool onLine();
    bool atIntersection();
    bool tokenSeen() const;
    Coord determineLocation() const;
};

#endif//CAMERA_H
