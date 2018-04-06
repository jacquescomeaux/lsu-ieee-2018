#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../../../RobotSource/include/Color.h"
#include "../../../RobotSource/include/Camera.h"

//bool tokenSeen() {
int main(int argc, char* argv[])
{
  Camera cam(2);

  cv::Mat image, img, hsvImg, mask;
  //cap >> image;
  image = cv::imread("Token.png", CV_LOAD_IMAGE_COLOR);
  static const unsigned int upperBound[3] = {64,67,80};
  img = image(cv::Rect(195,150,245,283));
  cv::cvtColor(img, hsvImg, cv::COLOR_BGR2HSV);
  cv::warpPerspective(hsvImg, hsvImg, M2, hsvImg.size());
  std::vector<cv::Vec3f> circles=getCircle(7);

  if(circles.empty()) return false;

  float x = circles[0][0];
  float y = circles[0][1];
  float r = circles[0][2];

  //const unsigned char hue_shift = 80;

  //for (int j = 0; j < hsv.rows; j++) {
  //  for (int i = 0; i < hsv.cols; i++) {
  //    unsigned char s = hsv.at<Vec3b>(j,i)[1];

  //    if (s + hue_shift > 255)
  //      s = (s + hue_shift) - 255;
  //    else
  //      s = s + hue_shift;

  //    hsv.at<Vec3b>(j,i)[1] = s;
  //  }
  //}

  mask = cv::Mat(283, 245, CV_64F, double(0)); //Look here
  cv::circle(hsvImg, (x,y), r, (255,255,255), -1);
  cv::Scalar hsvAverage = cv::mean(hsvImg, mask);

  float h = hsvAverage[0];
  float s = hsvAverage[1];
  float v = hsvAverage[2];

  if(h <= upperBound[0] && s <= upperBound[1] && v <= upperBound[2]) cout << "Token"; //return true;

  else cout << "No Token"; //return false;

}
