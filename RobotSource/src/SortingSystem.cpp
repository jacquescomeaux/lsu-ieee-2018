#include "../include/SortingSystem.h"
#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../../RobotSource/include/Color.h"

using namespace cv;

SortingSystem::SortingSystem() : token_cam(0) {}

void SortingSystem::pickUpToken() {
  transmitChar('p');
  receiveChar();
}

Color SortingSystem::checkTokenColor() {
  cv::Mat src;
  Rect roi;
  cv::VideoCapture tcam(0);
  tcam >> src;
  roi.x = 220;
  roi.y = 290;
  roi.width = 220;
  roi.height = 120;
  int h = 0;
  int s = 0;
  int v = 0;
  int sum = 0;
  //token_cam >> src;

  Mat img = src(roi);
  Mat hsv;
  cvtColor(img, hsv, cv::COLOR_BGR2HSV);

  for (int i = 0; i<roi.width; i++) {
    for (int j = 0; j<roi.height; j++) {
      h = h + hsv.at<Vec3b>(j,i)[0];
      s = s + hsv.at<Vec3b>(j,i)[1];
      v = v + hsv.at<Vec3b>(j,i)[2];
      sum = sum + 1;
    }
  }

  double avH = h/sum;
  double avV = v/sum;
  double avS = s/sum;

  Color tokenColor;
  
  if ((avS < 80) && (avV < 80)) tokenColor = Color::GRAY;
  else if (avH > 136) {
    if (avS > 141) tokenColor = Color::RED;
    else tokenColor = Color::MAGENTA;
  }
  else if (avS < 66) tokenColor = Color::CYAN;
  else if (avH < 68) tokenColor = Color::GREEN;
  else tokenColor = Color::BLUE;

  return tokenColor;

  /* static int c = 0;
  if(++c > 7) c = 1;
  return static_cast<Color>(c);*/
}

void SortingSystem::storeToken(Color c) const {
  transmitChar('r');
  transmitColor(c);
}

void SortingSystem::sortToken() {
  pickUpToken();
  storeToken(checkTokenColor());
}

void SortingSystem::dropTokenStack(Color c) {}
