#include "../include/Camera.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
#include <iostream>
#include <vector>

Camera::Camera() : Camera("untitled camera") {}

Camera::Camera(std::string n) {
  name = n;
}

int Camera::countLines() const {
  cv::VideoCapture cap(2);
  cv::Mat src, img, eroded, temp, element;
  cap >> src;
  cv::cvtColor(src, src, CV_BGR2GRAY);
  src = src(cv::Rect(200,165,235,240));
  //cv::bilateralFilter(src, img, 10, 250, 250);
  cv::threshold(src, img, 180, 255, cv::THRESH_BINARY_INV); 
  /*cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
  element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
  do {
    cv::erode(img, eroded, element);
    cv::dilate(eroded, temp, element);
    cv::subtract(img, temp, temp);
    cv::bitwise_or(skel, temp, skel);
    eroded.copyTo(img);
  } while(cv::countNonZero(img) != 0);
  */std::vector<cv::Vec4i> lines;
  HoughLinesP(img, lines, 1, CV_PI/180, 60, 10, 220 );
  std::cout << "numLines: " << lines.size() << std::endl;
  return lines.size();
}

std::string Camera::getName() const {
  return name;
}

bool Camera::onLine() const {
  return countLines() > 0;
}

bool Camera::atIntersection() const {
  return countLines() > 1;
}

bool Camera::tokenSeen() const {
  return true;
}

Coord Camera::determineLocation() const {return Coord(0,0);}
