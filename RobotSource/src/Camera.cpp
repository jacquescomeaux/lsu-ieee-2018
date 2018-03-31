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
  std::vector<cv::Point2f> pts_src, pts_dst;
  pts_src.push_back(cv::Point2f(88, 0));
  pts_src.push_back(cv::Point2f(143, 0));
  pts_src.push_back(cv::Point2f(69, 233));
  pts_src.push_back(cv::Point2f(173, 233));
  pts_dst.push_back(cv::Point2f(69, 0));
  pts_dst.push_back(cv::Point2f(135, 0));
  pts_dst.push_back(cv::Point2f(69, 233));
  pts_dst.push_back(cv::Point2f(135, 233));
  M = cv::getPerspectiveTransform(pts_src, pts_dst);
  for(int i = 0; i < 50; i++) countBlack();
}

int Camera::countBlack() {
  double t = (double)cv::getTickCount(); //for measuring performance
  cv::Mat img;
  cap >> img;
  if(img.empty()) return -1;
  cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
  img = img(cv::Rect(200, 165, 235, 233));
  cv::resize(img, img, cv::Size(), 0.5, 0.5);
  cv::threshold(img, img, 100, 255, cv::THRESH_BINARY_INV);
  warpPerspective(img, img, M, img.size());
  //cv::imshow("what the FUCK", img); 
  //cv::waitKey(0);
  int black = cv::countNonZero(img);
  t = ((double)cv::getTickCount() - t)/cv::getTickFrequency(); //num secs to complete function
  if(t > 1) std::cout << t << " sec\n";
  std::cout << "Blackness: " << black << std::endl;
  return black;
}

bool Camera::onLine() {
  int checkvals[2];
  for(int i = 0; i < 2; i++) checkvals[i] = countBlack();
  if(abs(checkvals[0]-checkvals[1]) > 4000) return false; //check for "trash frames"
  if(checkvals[0] > 2000 || checkvals[1] > 2000) {
    std::cout << "stopped at int with blackness "<< checkvals[0] << " or " << checkvals[1] << std::endl;
    return true;
  }
  else return false;
}

bool Camera::atIntersection() {
  int checkvals[2];
  for(int i = 0; i < 2; i++) checkvals[i] = countBlack();
  if(abs(checkvals[0]-checkvals[1]) > 4000) return false;
  if(checkvals[0] > 6000 || checkvals[1] > 6000) {
    std::cout << "stopped at int with blackness "<< checkvals[0] << " or " << checkvals[1] << std::endl;
    return true; 
  }
  else return false;
}

bool Camera::tokenSeen() const {
  return true;
}

Coord Camera::determineLocation() const {return Coord(0,0);}
