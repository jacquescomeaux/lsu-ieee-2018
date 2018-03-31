#include "../include/Camera.h"

#include <iostream>
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

Camera::Camera(int n) : cap(n) {
  //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
}

int Camera::countBlack() {
  //double t = (double)cv::getTickCount(); //for measuring performance
  cv::Mat src, src_gray;
  cap >> src;
  if(src.empty()) return -1;
  cv::Mat img = src(cv::Rect(200,165,235,233));
  cv::resize(img, img, cv::Size(), 0.75, 0.75);
  cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
  cv::threshold(img, img, 120, 255, cv::THRESH_BINARY_INV);
  //cv::imshow("what the FUCK", img); 
  //cv::waitKey(0);
  int black = cv::countNonZero(img);
  //t = ((double)cv::getTickCount() - t)/cv::getTickFrequency(); //num secs to complete function
  //std::cout << t << " sec\n";
  //std::cout << "Blackness: " << black << std::endl;

  return black;
}

bool Camera::onLine() {
  int checkvals[2];
  while(true) {
    for(int i = 0; i < 2; i++) checkvals[i] = countBlack();
    if(abs(checkvals[0]-checkvals[1]) < 500) break; //check for "trash frames"
  }
  if(checkvals[0] > 10) return true;
  else return false;
}

bool Camera::atIntersection() {
  int checkvals[2];
  while(true) {
    for(int i = 0; i < 2; i++) checkvals[i] = countBlack();
    if(abs(checkvals[0]-checkvals[1]) < 500) break;
  }
  if(checkvals[0] > 13000) return true;
  else return false;
}

bool Camera::tokenSeen() const {
  return true;
}

Coord Camera::determineLocation() const {return Coord(0,0);}
