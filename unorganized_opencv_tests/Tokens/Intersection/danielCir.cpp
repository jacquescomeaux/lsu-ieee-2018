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

  cv::Mat hsvImg, rgbImg, mask;
  static const unsigned int upperBound[3] = {64,67,80};

  std::vector<cv::Point2f> pts12, pts22;
  pts12.push_back(cv::Point2f(92,0));
  pts12.push_back(cv::Point2f(148,0));
  pts12.push_back(cv::Point2f(74,283));
  pts12.push_back(cv::Point2f(178,283));
  pts22.push_back(cv::Point2f(74,0));
  pts22.push_back(cv::Point2f(140,0));
  pts22.push_back(cv::Point2f(74,283));
  pts22.push_back(cv::Point2f(140,283));
  cv::Mat M2 = cv::getPerspectiveTransform(pts12, pts22);


  int Y1 = 150;
  int X1 = 195;
  int X2 = 440;
  unsigned int runcount = 0;

  runcount++;
  cv::Mat image, img;
  //for(int i = 0; i < 10; i++) cap >> image;
  image = imread("token1.png",CV_LOAD_IMAGE_COLOR);
  //cap >> image;
  img = image(cv::Rect(X1, Y1, X2-X1, 283)); //crop
  //cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);
  cv::Mat canny, canny2;

  cv::Mat gray;
  cv::Mat grayBI;
  /// Convert it to gray
  cv::cvtColor(img, gray, CV_BGR2GRAY);

  cv::warpPerspective(img, img, M2, img.size());

  //cv::bilateralFilter(gray, grayBI, 5, 75, 75);
  cv::GaussianBlur(gray, grayBI, cv::Size(0,0), 4);
  // compute canny (don't blur with that image quality!!)
  cv::Canny(grayBI, canny, 30, 40); //prev 200, 20
  //cv::namedWindow("canny"); cv::imshow("canny", canny>0);
  //cv::namedWindow("BLUR"); cv::imshow("BLUR", grayBI>0);


  std::vector<cv::Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 65, 60, 85); //60, 85

  if(circles.empty()) return false;

  float x = circles[0][0];
  float y = circles[0][1];
  float r = circles[0][2];
/*
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
*/
  //Rect boundRect(x-r, y-r, r*2+1, r*2+1);
  //Mat circleROI(stainMask, boundRect);

  cvtColor(img, hsvImg, CV_BGR2HSV);
  //Rect boundRect(x-r, y-r, r*2+1, r*2+1);
  //mask(stainMask_, boundRect);
  //mask = cv::Mat(283, 245, CV_64F, float(1)); //Look here
  mask(img.size(), CV_64F, float(0));
  cv::circle(hsvImg, Point(x,y), r, (255,255,255), -1);
  cv::Scalar hsvAverage = cv::mean(hsvImg, mask);

  float h = hsvAverage[0];
  float s = hsvAverage[1];
  float v = hsvAverage[2];

  imwrite("NoTokenGround.png", hsvImg);

  if(h <= upperBound[0] && s <= upperBound[1] && v <= upperBound[2]) cout << "True"; //return true;

  else cout << "False";

  return true;
}

