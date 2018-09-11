#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
//#include "../../RobotSource/include/Color.h"

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
  //VideoCapture cap(0);
  //if(!cap.isOpened()) return -1;

  Mat src, bgr;

  Rect roi;

  char ch;

  //roi.x = 220;
  //roi.y = 290;
  //roi.width = 220;
  //roi.height = 120;
  // BGR HSV
  // Blue 96, 34, 25, 116, 187, 96
  // Purple 77, 22, 92, 156, 193, 92
  // Green 116, 15, 72, 43, 220, 116
  // Red 28, 14, 99, 175, 214, 99
  // Yellow 


  int b = 0;
  int g = 0;
  int r = 0;
  int h = 0;
  int s = 0;
  int v = 0;
  int sum = 0;

  int maxB = 0;
  int minB = 0;
  int maxG = 0;
  int minG = 0;
  int maxR = 0;
  int minR = 0;
  int maxH = 0;
  int minH = 0;
  int maxS = 0;
  int minS = 0;
  int maxV = 0;
  int minV = 0;


  //cap >> src;
  src = imread("tokGrey.png", CV_LOAD_IMAGE_COLOR);
  if(src.empty()) return -1;

  //Mat img;
  //Mat img = src(roi);
  Mat hsv;

  //cout << "Here";

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

  cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);

  for (int i = 220; i<440; i++) {
    for (int j = 290; j<410; j++) {
      b = b + bgr.at<Vec3b>(j,i)[0];
      g = g + bgr.at<Vec3b>(j,i)[1];
      r = r + bgr.at<Vec3b>(j,i)[2];
      h = h + hsv.at<Vec3b>(j,i)[0];
      s = s + hsv.at<Vec3b>(j,i)[1];
      v = v + hsv.at<Vec3b>(j,i)[2];
      sum = sum + 1;
      if (b < minB) minB = b;
      if (b > maxB) maxB = b;
      if (g < minG) minG = g;
      if (g > maxG) maxG = g;
      if (r < minR) minR = r;
      if (r > maxR) maxR = r;
      if (h < minH) minH = h;
      if (h > maxH) maxH = h;
      if (s < minS) minS = s;
      if (s > maxS) maxS = s;
      if (v < minV) minV = v;
      if (v > maxV) maxV = v;
    }
  }

  imwrite("Crop.png", bgr);

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
  //Color tokenColor;

  //if ((avS < 80) && (avV < 80)) tokenColor = Color::GRAY;
  //else if (avH > 136) {
  //  if (avS > 141) tokenColor = Color::RED;
  //    else tokenColor = Color::YELLOW;
  //}
  //else if (avS < 66) tokenColor = Color::CYAN;
  //else if (avH < 68) tokenColor = Color::GREEN;
  //else tokenColor = Color::BLUE;


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

  cout << "MinB: " << minB << endl;
  cout << "MaxB: " << maxB << endl; 
  cout << "MinG: " << minG << endl; 
  cout << "MaxG: " << maxG << endl; 
  cout << "MinR: " << minR << endl; 
  cout << "MaxR: " << maxR << endl; 
  cout << "MinH: " << minH << endl; 
  cout << "MaxH: " << maxH << endl; 
  cout << "MinS: " << minS << endl; 
  cout << "MaxS: " << maxS << endl; 
  cout << "MinV: " << minV << endl; 
  cout << "MaxV: " << maxV << endl; 


  //return tokenColor;
}
