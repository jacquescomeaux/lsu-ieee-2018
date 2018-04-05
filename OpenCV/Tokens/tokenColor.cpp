#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../../RobotSource/include/Color.h"

using namespace cv;
using namespace std;

/** @function main */
Color main(int argc, char* argv[])
{
  VideoCapture cap(0);
  if(!cap.isOpened()) return -1;

  Mat src, bgr;

  //Rect roi;

  //roi.x = 220;
  //roi.y = 290;
  //roi.width = 220;
  //roi.height = 120;

  int h = 0;
  int s = 0;
  int v = 0;
  int sum = 0;

  cap >> src;
  //src = imread("tokGrey.png", CV_LOAD_IMAGE_COLOR);
  if(src.empty()) return -1;

  //Mat img = src(roi);
  Mat hsv;

  cvtColor(src, hsv, cv::COLOR_BGR2HSV);

  const unsigned char hue_shift = 80;

  for (int j = 0; j < hsv.rows; j++) {
    for (int i = 0; i < hsv.cols; i++) {
      unsigned char s = hsv.at<Vec3b>(j,i)[1];

      if (s + hue_shift > 255)
        s = (s + hue_shift) - 180;
      else
        s = s + hue_shift;

      hsv.at<Vec3b>(j,i)[1] = s;
    }
  }

  for (int i = 220; i<440; i++) {
    for (int j = 290; j<410; j++) {
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

  if (avS < 75) tokenColor = Color::GRAY;
  else if (avH > 160) tokenColor = Color::RED;
  else if ((avH > 130) && (avH < 160)) tokenColor = Color::MAGENTA;
  else if ((avH > 100) && (avH < 130)) tokenColor = Color::BLUE;
  else if ((avH > 75) && (avH < 100)) tokenColor = Color::CYAN;
  else if ((avH > 35) && (avH < 75)) tokenColor = Color::GREEN;
  else tokenColor = Color::YELLOW;

  return tokenColor;
}
