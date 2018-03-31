#include "../include/Camera.h"
 
#include <iostream>
#include <vector>

Camera::Camera(int n) : cap(n) {
  //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
}

int Camera::countLines() {
  double t = (double)cv::getTickCount(); //for measuring performance
  std::cout << "running count lines" << std::endl;
  cv::Mat src, src_gray;
  cap >> src;
  if(src.empty()) return -1;
  cv::Mat img = src(cv::Rect(200,165,235,233));
  cv::resize(img, img, cv::Size(), 0.75, 0.75);
  cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
  cv::threshold(img, img, 45, 255, cv::THRESH_BINARY_INV);
  //cv::imshow("what the FUCK", img); 
  //cv::waitKey(0);
  int white = cv::countNonZero(img);
  t = ((double)cv::getTickCount() - t)/cv::getTickFrequency(); //num secs to complete function
  std::cout << t << " sec\n";
  std::cout << "whiteness: " << white << std::endl;
  if(white > 8000) return 2;
  if(white < 200) return 0;
  return 1;
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
