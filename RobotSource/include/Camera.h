#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Coord.h"
#include "Color.h"
#include <string>
#include <vector>

class Camera {
  private:
    const double INCHES_PER_PIXEL;
    cv::VideoCapture cap;
    cv::Mat M, M2;
    int countBlack();
    std::vector<cv::Vec3f> getCircle(unsigned int); //looks for partial circle (token or intersection)
  public:
    Camera(int n);
    bool onLine();
    bool atIntersection();
    bool tokenSeen();
    Coord determineLocation() const;
    bool getTokenErrors(float*, float*);
    bool getTokenErrors(float*, float*, int); //errors given in pixels, might need some conversion to real world units
    Color getTokenColor();
    bool checkSortingPlate();
};

#endif//CAMERA_H
