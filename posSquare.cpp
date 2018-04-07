#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

// DETECT IF COLOR SQUARE IN FRAME
bool onSquare(Mat hsv, int iLH, int iLS, int iLV, int iHH, int iHS, int iHV)
{
  Mat imgTHR;

  inRange(hsv, Scalar(iLH, iLS, iLV), Scalar(iHH, iHS, iHV), imgTHR);

  erode(imgTHR, imgTHR, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
  dilate(imgTHR, imgTHR, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));

  dilate(imgTHR, imgTHR, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
  erode(imgTHR, imgTHR, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));

  Moments oMom = moments(imgTHR);

  double dM01 = oMom.m01;
  double dM10 = oMom.m10;
  double dArea = oMom.m00;

  // 10000 = SET AREA.  IF DETECTED AREA > 10000 -> COLOR DETECTED
  if (dArea > 2500) return true;
  else return false;
}

// MAIN
int main(int argc, char** argv)
{
  VideoCapture cap(1);

  if (!cap.isOpened()) return -1;

  int lRed = 160;
  int hRed = 179;
  int lYellow = 22;
  int hYellow = 38;
  int lGreen = 39;
  int hGreen = 69;
  int lCyan = 70;
  int hCyan = 100;
  int lBlue = 101;
  int hBlue = 130;
  int lMag = 131;
  int hMag = 159;

  int lowS = 50;
  int highS = 255;
  int lowV = 50;
  int highV = 255;

  Rect roi;
  roi.x = 0;
  roi.y = 240;
  roi.width = 640;
  roi.height = 240;

  Mat imgOrig, img, imgHSV;

  //bool loop = true;
  int iMag = 0;
  int iGreen = 0;

  while (True)
  {

    for (int i = 0; i < 10; i++) cap >> imgOrig;

    cap >> imgOrig;

    img = imgOrig(roi);

    cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    bool isRed = onSquare(imgHSV, lRed, lowS, lowV, hRed, highS, highV);
    bool isYellow = onSquare(imgHSV, lYellow, lowS, lowV, hYellow, highS, highV);
    bool isGreen = onSquare(imgHSV, lGreen, lowS, lowV, hGreen, highS, highV);
    bool isCyan = onSquare(imgHSV, lCyan, lowS, lowV, hCyan, highS, highV);
    bool isBlue = onSquare(imgHSV, lBlue, lowS, lowV, hBlue, highS, highV);
    bool isMag = onSquare(imgHSV, lMag, lowS, lowV, hMag, highS, highV);

    if (isMag) || (isYellow) iMag++;
    if (isGreen) || (isRed)  iGreen++;

    if ((iMag > 0) && (iGreen > 0)) {
      iMag = 0;
      iGreen = 0;
    }

   if (iMag == 5) return false;
   if (iGreen == 5) return true;
  }
}
