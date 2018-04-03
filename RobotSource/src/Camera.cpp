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
  int X1 = 195;
  int X2 = 440;

  std::vector<cv::Vec3f> circles;
  for(int a = 0; a < attempts; a++) {
    cv::Mat image, img, dst, dst1;
    cap >> image;

    img = image(cv::Rect(X1, Y1, X2-X1, 283));
    cv::warpPerspective(img, dst, M, img.size());
    //cv::warpPerspective(img, img, M, img.size());
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
    if(!circles.empty()) break;
  }
  return circles;
}

bool Camera::intersectionInFrame() {
  if(checkCircle(5).size() > 0) {
  std::cout << "intersectionInFrame(): Intersection Found" << std::endl;
  return true;
  }
  else if(checkPartialCircle(5).size() > 0) {
    std::vector<cv::Vec3f> center = checkPartialCircle(5);
    for(int i = 0; i < center.size(); i++) {
      if(center[i][2] > 60 || center[i][2] < 90) {
	std::cout << "Partial intersection found" << std::endl;
	return true;
      }
      else return false;
    }
  }
  else {
  std::cout << "intersectionInFrame(): No intersection found..." << std::endl;
  return false;
  }
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
  if(intersectionInFrame()) center = checkCircle(att);
  else center = checkPartialCircle();
  if(!center.empty() && (intersectionInFrame() || partialIntersectionInFrame())) {
    int tolerance = 10; //allowable number of pixels to be off target, needs testing
    float currentx = xtarget - center[center.size() - 1][0];
    float currenty = center[center.size() - 1][1] - ytarget;
    std::cout << "getTokenErrors Corrections: x=" << currentx << " y=" << currenty << std::endl;
    *x = currentx * INCHES_PER_PIXEL;
    *y = currenty * INCHES_PER_PIXEL;
    if(std::abs(currentx) <= tolerance) *x = 0;
    if(std::abs(currenty) <= tolerance) *y = 0;
  }
}

std::vector<cv::Vec3f> Camera::checkPartialCircle(int attempts = 1) { //NOTE: ALSO DETECTS INTERSECTIONS
  int Y1 = 150;
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
  while(int i = 0; i < attempts; i++) {
    cv::Mat image, img;
    cap >> image;
    img = image(cv::Rect(X1, Y1, X2-X1, 283)); //crop
    cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);
    cv::warpPerspective(img, img, M, img.size());
    
    cv::Mat canny, gray, grayBI;
    cv::cvtColor(img, gray, CV_BGR2GRAY );
    cv::bilateralFilter(gray, grayBI, 5, 75, 75);
    cv::Canny(grayBI, canny, 200,20); //prev 200, 20
    std::vector<cv::Vec3f> circles;
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
      
      //TODO: maybe paramter incrementation might depend on circle size!
      for(float t =0; t<2*3.14159265359f; t+= 0.1f) {
	counter++;
	float cX = radius*cos(t) + circles[i][0];
	float cY = radius*sin(t) + circles[i][1];
	
	if(dt.at<float>(cY,cX) < maxInlierDist) inlier++; 
      }
      std::cout << 100.0f*(float)inlier/(float)counter << " % of a circle with radius " << radius << " detected" << std::endl;
      //radius should be 60 - 70
    }
    if(!circles.empty()) break; 
  }
  return circles;
}
