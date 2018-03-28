#include "../include/Camera.h"
 
#include <iostream>
#include <vector>

Camera::Camera(int n) : cap(n) {}

int Camera::countLines() {
  std::cout << "wow" << std::endl;
  cv::Mat src, img, eroded, temp, element;
  cap >> src;
  cv::cvtColor(src, src, CV_BGR2GRAY);
  src = src(cv::Rect(200,165,235,240)); //crop image
  cv::resize(src, src, cv::Size(), 0.7, 0.7, cv::INTER_LANCZOS4);
  //cv::bilateralFilter(src, img, 10, 250, 250); //smoothes colors but leaves edges sharp
  cv::threshold(src, img, 180, 255, cv::THRESH_BINARY_INV); //anything darker than 180 becomes white, lighter becomes black
  cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
  element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
  //std::cout << "wow" << std::endl;
  do {
    cv::erode(img, eroded, element);
    cv::dilate(eroded, temp, element);
    cv::subtract(img, temp, temp);
    cv::bitwise_or(skel, temp, skel);
    eroded.copyTo(img);
//    std::cout << "wow" << std::endl;
  } while(cv::countNonZero(img) != 0);
  std::vector<cv::Vec4i> lines;
  HoughLinesP(skel, lines, 1, CV_PI/180, 60, 10, 220);
  //return cv::countNonZero(skel) > 100;
  
//  std::cout << "numLines: " << lines.size() << std::endl;
  return lines.size();
}

bool Camera::onLine() {
  return countLines() > 0;
}

bool Camera::atIntersection() {
  return countLines() > 1;
}

bool Camera::tokenSeen() const {
  return true;
}

Coord Camera::determineLocation() const {return Coord(0,0);}
