#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Coord.h"
#include <string>
#include <vector>

class Camera {
  private:
    const double INCHES_PER_PIXEL;
    cv::VideoCapture cap;
    cv::Mat M;
    int countBlack();
    std::vector<cv::Vec3f> checkCircle(int); //looks for a circle in current frame. Argument is optional (default 1) and tells function how many times to check for a circle
  public:
    Camera(int n);
    bool onLine();
    bool atIntersection();
    bool tokenSeen() const;
    Coord determineLocation() const;
    
    bool intersectionInFrame(); //true if circle can be detected
    bool tokenCentered();//true if token arm is cleared
    void getTokenErrors(float*, float*); //errors given in pixels, might need some conversion to real world units
    void getTokenErrors(float*, float*, int); //errors given in pixels, might need some conversion to real world units
};

#endif//CAMERA_H
