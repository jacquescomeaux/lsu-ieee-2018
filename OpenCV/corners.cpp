#include <opencv2/opencv.hpp> 
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

vector<Vec4i> hierarchy;

int main() {
  VideoCapture cap(0);
  if(!cap.isOpened()) return -1;
  while(true) {
    Mat m, mThresh, mc, bwM;
    cap >> m;
    //threshold(m, mThresh, 80, 255, THRESH_BINARY);
    //cvtColor(mThresh, bwM, CV_RGB2GRAY);
    //findContours(bwM, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE, cv::Point(0,0));
    imshow("Image", m);
    /*mc = Mat::zeros(m.size(), CV_8UC3);
    drawContours(mc, contours, 0, Scalar(255, 0, 0), 1);
    vector<Point> approx;
    double d = 0;
    do {
      d++;
      approxPolyDP(contours[0], approx, d, true);
      cout << approx.size() << " " << d << endl;
    } while (approx.size() > 4);
    contours.push_back(approx);
    drawContours(mc, contours, contours.size() - 1, Scalar(0, 0, 255), 1);
    imshow("Ctr", mc);
    waitKey();
   */}
  return 0;
}
