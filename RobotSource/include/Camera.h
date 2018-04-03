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
    cv::Mat M, M2;
    int countBlack();
    std::vector<cv::Vec3f> checkCircle(int);//looks for a full circle (token) in current frame.
    std::vector<cv::Vec3f> checkPartialCircle(int); //looks for partial circle (token or intersection)
  public:
    Camera(int n);
    bool onLine();
    bool atIntersection();
    bool tokenSeen();
    Coord determineLocation() const;
    
    bool intersectionInFrame(); //true if circle can be detected
    bool tokenCentered(); //true if token arm is cleared
    void getTokenErrors(float*, float*);
    void getTokenErrors(float*, float*, int); //errors given in pixels, might need some conversion to real world units
    std::vector<double> readToken(); //returns vector of hsv values to detect color
};

#endif//CAMERA_H
