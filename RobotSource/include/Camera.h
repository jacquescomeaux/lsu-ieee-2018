#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Coord.h"
#include <string>
#include <vector>

class Camera {
  private:
    cv::VideoCapture cap;
    cv::Mat M;
    int countBlack();
    std::vector<cv::vec3f> checkCircle(int); //looks for a circle in current frame. Argument is optional (default 1) and tells function how many times to check for a circle
  public:
    Camera(int n);
    bool onLine();
    bool atIntersection();
    bool tokenSeen() const;
    Coord determineLocation() const;
    
    bool intersectionInFrame(); //true if circle can be detected
    bool tokenCentered();//true if token arm is cleared
    void getTokenErrors(int*, int*, int); //errors given in pixels, might need some conversion to real world units
};

#endif//CAMERA_H
