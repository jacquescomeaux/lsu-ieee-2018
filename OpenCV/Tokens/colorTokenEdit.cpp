#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
//#include "../../RobotSource/include/Color.h"

using namespace cv;
using namespace std;

/** @function main */
Color Camera::getTokenColor() {
  cv::Mat src, bgr;
  cv::Rect roi;

  char ch;

  roi.x = 220;
  roi.y = 290;
  roi.width = 220;
  roi.height = 120;
  // BGR HSV
  // Blue 96, 34, 25, 116, 187, 96
  // Purple 77, 22, 92, 156, 193, 92
  // Green 116, 15, 72, 43, 220, 116
  // Red 28, 14, 99, 175, 214, 99
  // Yellow:
  // Cyan: 104, 103, 58 | 90, 114, 106


  int b = 0;
  int g = 0;
  int r = 0;
  int h = 0;
  int s = 0;
  int v = 0;
  int sum = 0;

  cv::Mat img = src(roi);
  cv::Mat hsv;

  cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

  const unsigned char hue_shift = 80; //this is actually saturation shift

  for (int j = 0; j < hsv.rows; j++) {
    for (int i = 0; i < hsv.cols; i++) {
      unsigned char s = hsv.at<Vec3b>(j,i)[1];

      if (s + hue_shift > 255)
        s = (s + hue_shift) - 180; // <-- what??
      else
        s = s + hue_shift;

      hsv.at<Vec3b>(j,i)[1] = s;
    }
  }

  cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);

  for (int i = 220; i<440; i++) {
    for (int j = 290; j<410; j++) {
      b = b + bgr.at<cv::Vec3b>(j,i)[0];
      g = g + bgr.at<cv::Vec3b>(j,i)[1];
      r = r + bgr.at<cv::Vec3b>(j,i)[2];
      h = h + hsv.at<cv::Vec3b>(j,i)[0];
      s = s + hsv.at<cv::Vec3b>(j,i)[1];
      v = v + hsv.at<cv::Vec3b>(j,i)[2];
      sum++;
    }
  }

  double avB = b/sum;
  double avG = g/sum;
  double avR = r/sum;

  double avH = h/sum;
  double avV = v/sum;
  double avS = s/sum;
  Color tokenColor = Color::NONE;
  // RGB Color Detection
  if(avB > 70 && avR > 90) {
    tokenColor = Color::MAGENTA;
    std::cout << "Magenta detected" << std::endl;
  }
  if(avB > 90) {
    if(avG > 90) {
    tokenColor = Color::CYAN;
    std::cout << "Cyan detected" << std::endl;
    }
    else {
      tokenColor = Color::BLUE;
      std::cout << "Blue detected" << std::endl;
    }
  }
  if(avG > 90) {
    if(avR < 90) {
      tokenColor = Color::GREEN;
      std::cout << "Green detected" << std::endl;
    }
    else {
      tokenColor = Color::YELLOW;
      std::cout << "Yellow detected" << std::endl;
    }
  }
  if(avR > 90) {
    tokenColor = Color::RED;
    std::cout << "Red detected" << std::endl;
  }

  std::cout << "(B, G, R): (" << avB << ", " << avG << ", " << avR << ")" << std::endl;

  //cout << "H: " << avH << endl;
  //cout << "S: " << avS << endl;
  //cout << "V: " << avV << endl;

  return tokenColor;
}
