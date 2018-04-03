#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
  //VideoCapture cap(1);
  //if(!cap.isOpened()) return -1;

  Mat src, src_gray;

  Rect roi;

  int lVCya = 

  roi.x = 220;
  roi.y = 290;
  roi.width = 220;
  roi.height = 120;
  //Green: 200->421, 300->421
  //Cyan: 180->400,  340->460

 src = imread("tokPurple.png", CV_LOAD_IMAGE_COLOR);
  if(src.empty()) return -1;

  Mat img = src(roi);
  Mat hsv;

  //cout << "Here";

  cvtColor(img, hsv, cv::COLOR_BGR2HSV);

