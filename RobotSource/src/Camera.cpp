#include "../include/Camera.h"
#include <cmath>
#include <iostream>
#include <exception>
#include <vector>

//adding these trying to get ryan's color detection to work...
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"

/* Approximate values of Blackness for countBlack(Threshold: 120,255)
Corner Intersection (with token)
	Centered: 20,500 +/- 250
	Off-centered: >= 14,000
-----------------------------------------------
Cross Intersection (with token)
	Centered: 16,000 +/- 50
	Off-centered: Min:13,000 || Max: 18,300
-----------------------------------------------
Lines
	Parallel: 9,950 (MAX)
	Perpendicular: 11,950 (MAX)
*/

Camera::Camera(int n) : INCHES_PER_PIXEL(0.00839223), cap(n) {
  //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
  std::vector<cv::Point2f> pts_src, pts_dst;
  pts_src.push_back(cv::Point2f(88, 0));
  pts_src.push_back(cv::Point2f(143, 0));
  pts_src.push_back(cv::Point2f(69, 233));
  pts_src.push_back(cv::Point2f(173, 233));
  pts_dst.push_back(cv::Point2f(69, 0));
  pts_dst.push_back(cv::Point2f(139, 0));
  pts_dst.push_back(cv::Point2f(69, 233));
  pts_dst.push_back(cv::Point2f(139, 233));
  M = cv::getPerspectiveTransform(pts_src, pts_dst);
  //for(int i = 0; i < 50; i++) countBlack();
  std::vector<cv::Point2f> pts12, pts22;
  pts12.push_back(cv::Point2f(92,0));
  pts12.push_back(cv::Point2f(148,0));
  pts12.push_back(cv::Point2f(74,283));
  pts12.push_back(cv::Point2f(178,283));
  pts22.push_back(cv::Point2f(74,0));
  pts22.push_back(cv::Point2f(140,0));
  pts22.push_back(cv::Point2f(74,283));
  pts22.push_back(cv::Point2f(140,283));
  M2 = cv::getPerspectiveTransform(pts12, pts22);

}

int Camera::countBlack() {
  double t = (double)cv::getTickCount(); //for measuring performance
  cv::Mat img;
  cap >> img;
  if(img.empty()) return -1;
  cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
  img = img(cv::Rect(200, 165, 235, 233));
  cv::threshold(img, img, 130, 255, cv::THRESH_BINARY_INV);
  warpPerspective(img, img, M, img.size());
  img = img(cv::Rect(10, 0, 180, 170));
  cv::resize(img, img, cv::Size(), 0.1, 0.1);
  int black = cv::countNonZero(img);
  t = ((double)cv::getTickCount() - t)/cv::getTickFrequency(); //num secs to complete function
  //if(t > 1) std::cout << t << " sec\n";
  //std::cout << "Blackness: " << black << std::endl;
  return black;
}

bool Camera::onLine() {
  if(countBlack() > 100) return true;
  else return false;
}

bool Camera::atIntersection() {
  if(countBlack() > 160) {
  //std::cout << "stopped at int with blackness "<< checkvals[0] << " or " << checkvals[1] << std::endl;
    return true;
  }
  else return false;
}

bool Camera::tokenSeen() {
  if(tokenInFrame(2)) return true;
  else return false;
}

Coord Camera::determineLocation() const {return Coord(0,0);}

std::vector<cv::Vec3f> Camera::checkCircle(int attempts = 1) { //Only detects token circles
  int Y1 = 150;
  int X1 = 195;
  int X2 = 440;

  std::vector<cv::Vec3f> circles;
  for(int a = 0; a < attempts; a++) {
    cv::Mat image, img, dst, dst1;
    cap >> image;

    img = image(cv::Rect(X1, Y1, X2-X1, 283));
    cv::warpPerspective(img, dst, M2, img.size());
    cv::cvtColor(dst, dst1, CV_BGR2GRAY);
    cv::bilateralFilter(dst1, dst, 5, 75, 75);
    cv::Canny(dst, dst, 50, 60);

    //HoughCircles(input, output, method, dp,
    //minDist - min dist between centers
    //param1 - higher threshold of the 2 passed to Canny() (the lower one is twice smaller)
    //param2 - accumlator threshold for the circle centers at detection stage
    //minRadius - Minimum circle radius
    //maxRadius - Maximum circle radius
    cv::HoughCircles(dst, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 65, 60, 70);
    //if (!circles.empty()) std::cout << "Circle Detected: (" << circles[0][0] << "," << circles[0][1] << ")" << std::endl;
    if(!circles.empty()) break;
  }
  return circles;
}

bool Camera::intersectionInFrame() {
  std::vector<cv::Vec3f> center = checkPartialCircle(5);
  for(unsigned int i = 0; i < center.size(); i++) {
    if(center[i][2] > 50 || center[i][2] < 100) return true;
  }
  return false;
}

bool Camera::tokenInFrame() {
  if(tokenInFrame(1)) return true;
  else return false;
}

bool Camera::tokenInFrame(int att) {
  if(checkCircle(att).size() > 0) return true;
  else return false;
}

bool Camera::tokenCentered() {
  int certainty = 0; //counter to make sure centered value is correct;

  for(int i = 0; i < 5; i++) {
    float checkx = 0;
    float checky = 0;
    getTokenErrors(&checkx, &checky);
    if(checkx == 0 && checky == 0) certainty++;
    else certainty--;
  }

  if(certainty > 0) return true;
  else return false;
}

void Camera::getTokenErrors(float* x, float* y) {
  getTokenErrors(x, y, 1);
}

void Camera::getTokenErrors(float* x, float*y, int att) {
  static const int xtarget = 105;
  static const int ytarget = 120;
  std::vector<cv::Vec3f> center;
  center = checkCircle(att);
  if (center.empty()) center = checkPartialCircle(att);
  if(!center.empty()) {
    int tolerance = 24; //allowable number of pixels to be off target, needs testing
    float currentx = xtarget - center[center.size() - 1][0];
    float currenty = center[center.size() - 1][1] - ytarget;
    //std::cout << "getTokenErrors(): x=" << currentx << " y=" << currenty << std::endl;
    *x = currentx * INCHES_PER_PIXEL;
    *y = currenty * INCHES_PER_PIXEL;
    if(std::abs(currentx) <= tolerance) *x = 0;
    if(std::abs(currenty) <= tolerance) *y = 0;
  }
}

std::vector<cv::Vec3f> Camera::checkPartialCircle(int attempts = 1) { //Detects both intersection and token circles
  int Y1 = 150;
  int X1 = 195;
  int X2 = 440;
  
  std::vector<cv::Vec3f> circles;
  for(int i = 0; i < attempts; i++) {
    cv::Mat image, img;
    cap >> image;
    img = image(cv::Rect(X1, Y1, X2-X1, 283)); //crop
    cv::warpPerspective(img, img, M2, img.size());
    
    cv::Mat canny, gray, grayBI;
    cv::cvtColor(img, gray, CV_BGR2GRAY );
    cv::bilateralFilter(gray, grayBI, 5, 75, 75);
    cv::Canny(grayBI, canny, 200,20);
    cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 100, 50, 90 );
    
    //compute distance transform:
    cv::Mat dt;
    cv::distanceTransform(255-(canny>0), dt, CV_DIST_L2 ,3);
    
    // test for semi-circles:
    float minInlierDist = 2.0f;
    for( size_t i = 0; i < circles.size(); i++ ) 
    {
      // test inlier percentage:
      // sample the circle and check for distance to the next edge
      unsigned int counter = 0;
      unsigned int inlier = 0;
      
      cv::Point2f center((circles[i][0]), (circles[i][1]));
      float radius = (circles[i][2]);
      
      // maximal distance of inlier might depend on the size of the circle
      float maxInlierDist = radius/25.0f;
      if(maxInlierDist<minInlierDist) maxInlierDist = minInlierDist;
      
      //TODO: maybe parameter incrementation might depend on circle size!
      //wow
      for(float t =0; t<2*3.14159265359f; t+= 0.1f) {
	counter++;
	float cX = radius*cos(t) + circles[i][0];
	float cY = radius*sin(t) + circles[i][1];
	
	if(dt.at<float>(cY,cX) < maxInlierDist) inlier++; 
      }
      //std::cout << 100.0f*(float)inlier/(float)counter << " % of a circle with radius " << radius << " detected" << std::endl;
      //radius should be 60 - 70
    }
    if(!circles.empty()) break;
  }
  return circles;
}

std::vector<double> Camera::readToken() {
  cv::Mat src;
  cv::Rect roi;
  cap >> src;
  roi.x = 220;
  roi.y = 290;
  roi.width = 220;
  roi.height = 120;
  int h = 0;
  int s = 0;
  int v = 0;
  int sum = 0;

  cv::Mat img = src(roi);
  cv::Mat hsv;
  cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
  for (int i = 0; i < roi.width; i++) {
    for (int j = 0; j < roi.height; j++) {
      h = h + hsv.at<cv::Vec3b>(j,i)[0];
      s = s + hsv.at<cv::Vec3b>(j,i)[1];
      v = v + hsv.at<cv::Vec3b>(j,i)[2];
      sum = sum + 1;
    }
  }

  std::vector<double> hvs;
  hvs.push_back(h/sum);
  hvs.push_back(v/sum);
  hvs.push_back(s/sum);

  return hvs;
}
