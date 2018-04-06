#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
//#include "../../../RobotSource/include/Color.h"
//#include "../../../RobotSource/include/Camera.h"

using namespace std;
using namespace cv;

//bool tokenSeen() {
int main(int argc, char* argv[])
{
  //Camera cam(2);

  Mat image, img, hsvImg, mask, rgbImg;
  //cap >> image;
  image = imread("notoken3.png", CV_LOAD_IMAGE_COLOR);
  static const unsigned int upperBound[3] = {64,67,80};
  img = image(Rect(195,150,245,283));
  
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

  cvtColor(img, hsvImg, cv::COLOR_BGR2HSV);
  cv::warpPerspective(hsvImg, hsvImg, M2, hsvImg.size());
  std::vector<cv::Vec3f> circles=getCircle(7);

  if(circles.empty()) return false;

  float x = circles[0][0];
  float y = circles[0][1];
  float r = circles[0][2];

  const unsigned char hue_shift = 80;
 
  for (int j = 0; j < hsvImg.rows; j++) {
    for (int i = 0; i < hsvImg.cols; i++) {
      unsigned char s = 255; //hsvImg.at<Vec3b>(j,i)[1];
      unsigned char v = 100; //hsvImg.at<Vec3b>(j,i)[2];
      hsvImg.at<Vec3b>(j,i)[1] = s;
      hsvImg.at<Vec3b>(j,i)[2] = v;
  //.    if (s + hue_shift > 255)
  //      s = (s + hue_shift) - 255;
  //    else
  //      s = s + hue_shift;

  //    hsv.at<Vec3b>(j,i)[1] = s;
    }
  }

  cvtColor(hsvImg, rgbImg, cv::COLOR_HSV2BGR);
  mask = cv::Mat(283, 245, CV_64F, double(0)); //Look here
  cv::circle(hsvImg, (x,y), r, (255,255,255), -1);
  cv::Scalar hsvAverage = cv::mean(hsvImg, mask);

  float h = hsvAverage[0];
  float s = hsvAverage[1];
  float v = hsvAverage[2];

  imwrite("NoTokenGround.png", hsvImg);

  if(h <= upperBound[0] && s <= upperBound[1] && v <= upperBound[2]) cout << "Token"; //return true;

  else cout << "No Token"; //return false;

  return true;
}
