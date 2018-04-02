#include "../include/Camera.h"
#include <cmath>
#include <iostream>
#include <exception>
#include <vector>

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
  //int checkvals[2];
  //for(int i = 0; i < 2; i++) checkvals[i] = countBlack();
  //if(abs(checkvals[0]-checkvals[1]) > 2000) return false; //check for "trash frames"
  //if(checkvals[0] > 2500 || checkvals[1] > 2500) {
    if(countBlack() > 100) {
    //std::cout << "stopped at line with blackness "<< checkvals[0] << " or " << checkvals[1] << std::endl;
    return true;
  }
  else return false;
}

bool Camera::atIntersection() {
  //int checkvals[2];
  //for(int i = 0; i < 2; i++) checkvals[i] = countBlack();
  //if(abs(checkvals[0]-checkvals[1]) > 2000) return false;
  //if(checkvals[0] > 5000 || checkvals[1] > 5000) {
  if(countBlack() > 160) {
  //std::cout << "stopped at int with blackness "<< checkvals[0] << " or " << checkvals[1] << std::endl;
    return true;
  }
  else return false;
}

bool Camera::tokenSeen() const {
  return true;
}

Coord Camera::determineLocation() const {return Coord(0,0);}

std::vector<cv::Vec3f> Camera::checkCircle(int attempts = 1) { //argument for num times to check for token. Can run ~5-8 times per second.
  int Y1 = 150;
  //int Y2 = 400;
  int X1 = 195;
  int X2 = 440;
  
  std::vector<cv::Point2f> pts1, pts2;
  
  pts1.push_back(cv::Point2f(92,0));
  pts1.push_back(cv::Point2f(148,0));
  pts1.push_back(cv::Point2f(74,283));
  pts1.push_back(cv::Point2f(178,283));
  
  pts2.push_back(cv::Point2f(74,0));
  pts2.push_back(cv::Point2f(140,0));
  pts2.push_back(cv::Point2f(74,283));
  pts2.push_back(cv::Point2f(140,283));
  
  std::vector<cv::Vec3f> circles;
  for(int a = 0; a < attempts; a++) {
    cv::Mat image, img, dst, dst1;
    cap >> image;
    //if(image.empty()) return -1;
    
    img = image(cv::Rect(X1, Y1, X2-X1, 283));
    cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);
    cv::warpPerspective(img, dst, M, img.size());
    cv::warpPerspective(img, img, M, img.size());
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
    if (!circles.empty()) std::cout << "Circle Detected: (" << circles[0][0] << "," << circles[0][1] << ")" << std::endl;
    //t = (cv::getTickCount() - t)/cv::getTickFrequency(); //Run Time Per Loop(ms): 120(BEST) - 200(WORST)
    //std::cout << "Time: " << t << std::endl;
    
    if(!circles.empty()) break;
    /*try {
      if(!circles.empty()) {
	return circles;
	*//*int x = round(circles[i][0]);
	int y = round(circles[i][1]);
	int radius = round(circles[i][2]);
	cv::Point center(x,y);
	std::cout << "Circle Detected: (" << center.x << "," << center.y << ") radius: " << radius << std::endl; 
	cv::circle(img, center, radius, cv::Scalar(0,255,0), 4); */
      /*}
      //else return 0;
    }
    catch(std::exception& e) {
      std::cout << "Exception Thrown" << e.what() << std::endl;
    }*/
    //cv::imshow("output", img); //for debugging
    //cv::imshow("dst", dst);
  }//end while(true)
  return circles;
}

bool Camera::intersectionInFrame() {
  if(checkCircle(10).size() > 0) {
  std::cout << "intersectionInFrame(): Intersection Found" << std::endl;
  return true;
  }
  else {
  std::cout << "intersectionInFrame(): No intersection found..." << std::endl;
  return false;
  }
}

bool Camera::tokenCentered() {
  float checkx = 0;
  float checky = 0;
  getTokenErrors(&checkx, &checky);
  if(checkx == 0 && checky == 0) {
  std::cout << "tokenCentered(): Robot is centered!" << std::endl;
  return true;
  }
  else {
  std::cout << "tokenCentered(): Robot not centered..." << std::endl;
  return false;
  }
}

void Camera::getTokenErrors(float* x, float* y) {
  getTokenErrors(x, y, 1);
}

void Camera::getTokenErrors(float* x, float*y, int att) {
  static const int xtarget = 150;
  static const int ytarget = 130;
  std::vector<cv::Vec3f> center;
  center = checkCircle(att); //if multiple reads are needed to avoid trash values
  if(!center.empty() && intersectionInFrame()) {
    std::cout << "getTokenErrors(): Circle Found" << std::endl;
    int tolerance = 1; //allowable number of pixels to be off target, needs testing
    float currentx = center[center.size() - 1][0] - xtarget;
    float currenty = center[center.size() - 1][1] - ytarget;
    std::cout << "getTokenErrors Corrections: x=" << currentx << " y=" << currenty << std::endl;
    if(abs(currentx) <= tolerance && abs(currenty) <= tolerance) *x = *y = 0;
    else {
	*x = currentx * INCHES_PER_PIXEL;
	*y = currenty * INCHES_PER_PIXEL;
    }
  }
}
