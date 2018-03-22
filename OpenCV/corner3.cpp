#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using namespace cv;
using namespace std;
 
int thresh = 100;
 
int main() {
  cv::VideoCapture cap(1);
  if(!cap.isOpened()) return -1;
  Mat src, gray, dst, dst_norm, dst_norm_scaled;
  while(true) {
    cap >> src;
    cvtColor(src, gray, CV_BGR2GRAY);
    dst = Mat::zeros(src.size(), CV_32FC1);
    cornerHarris(gray, dst, 7, 5, 0.05, BORDER_DEFAULT);
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);
    for(int i = 0; i < dst_norm.rows; i++) for(int j = 0; j < dst_norm.cols; j++)
      if(static_cast<int>(dst_norm.at<float>(i,j)) > thresh) circle(dst_norm_scaled, Point(j, i), 5,  Scalar(0), 2, 8, 0);
    namedWindow("corners_window");//, CV_WINDOW_AUTOSIZE);
    resizeWindow("corners_window", 500, 500);
    imshow("corners_window", dst_norm_scaled);
    waitKey(0);
    //if(cv::waitKey(33) >= 0) break;
  }
  return(0);
}
