#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../../RobotSource/include/Color.h"

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
  //VideoCapture cap(1);
  //if(!cap.isOpened()) return -1;

  Mat src, src_gray;

  Rect roi;

  char ch;

  roi.x = 220;
  roi.y = 290;
  roi.width = 220;
  roi.height = 120;
  //Green: 200->421, 300->421
  //Cyan: 180->400,  340->460

  int b = 0;
  int g = 0;
  int r = 0;
  int h = 0;
  int s = 0;
  int v = 0;
  int sum = 0;

  //cap >> src;
  src = imread("tokBlue.png", CV_LOAD_IMAGE_COLOR);
  if(src.empty()) return -1;

  Mat img = src(roi);
  Mat hsv;

  //cout << "Here";

  cvtColor(img, hsv, cv::COLOR_BGR2HSV);

  for (int i = 0; i<roi.width; i++) {
    for (int j = 0; j<roi.height; j++) {
      b = b + img.at<Vec3b>(j,i)[0];
      g = g + img.at<Vec3b>(j,i)[1];
      r = r + img.at<Vec3b>(j,i)[2];
      h = h + hsv.at<Vec3b>(j,i)[0];
      s = s + hsv.at<Vec3b>(j,i)[1];
      v = v + hsv.at<Vec3b>(j,i)[2];
      sum = sum + 1;
    }
  }

  imwrite("Crop.png", img);

  double avB = b/sum;
  double avG = g/sum;
  double avR = r/sum;

  double avH = h/sum;
  double avV = v/sum;
  double avS = s/sum;

  //double bG = avB / avG;
  //double rG = avR / avG;
  //double hS = avH / avS;
  //double bGbR = bG * rG;
  //cout << bGbR << endl;

  //cout << bG << endl;
  Color tokenColor;

  if ((avS < 80) && (avV < 80)) cout << "Grey";
  else if (avH > 136) {
    if (avS > 141) cout << "Red";
      else cout << "Purple";
  }
  else if (avS < 66) cout << "Cyan";
  else if (avH < 68) cout << "Green";
  else cout << "Blue";


  /*
  if (hS > 3)
    cout << "Grey";
  else if (bG < 0.8) {
    if (hS > 0.43)
      cout << "Cyan";
    else cout << "Green";
  }
  else {
    if (bG > 0.8)
      cout << "Blue";
    else if (rG > 2.0)
      cout << "Red";
    else cout << "Purple";
  } 
  */
  // RGB Color Detection
  /*
  if (avB > 95) && (avB < 125) {
    if (avG > 90) cout << "Blue";
    else cout << "Gray";
  }

  if (avB > 140) && (avB < 170) cout << "Red";

  if (avB > 60) && (avB < 90) {
    if (avR > 100) cout << "Cyan";
    else if (avG > 55) cout << "Yellow";
    else cout << "Green";
  }
  */

  cout << "B: " << avB << endl;
  cout << "G: " << avG << endl;
  cout << "R: " << avR << endl;

  cout << "H: " << avH << endl;
  cout << "S: " << avS << endl;
  cout << "V: " << avV << endl;
}
