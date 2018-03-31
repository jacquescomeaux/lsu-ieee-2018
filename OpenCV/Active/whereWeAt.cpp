#include <iostream>
#include <stdio.h>
//#include "opencv2/features2d.hpp"
#include "opencv2/core/core.hpp"
//#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/xfeatures2d.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;


/** @function main */
int main(int argc, char** argv)
{
  VideoCapture cap(1);
  if(!cap.isOpened()) return -1;

  Mat src, src_gray;
  Rect roi;

  char ch;

  roi.x = 195;
  roi.y = 117;
  roi.width = 245;
  roi.height = 240;

  //while (true) {
  /// Read the image
    cap >> src;
    if(src.empty()) return -1;

    Mat img = src(roi);

    cvtColor(img, img, cv::COLOR_BGR2GRAY);

    threshold(img, img, 45, 255, THRESH_BINARY);

    int white = countNonZero(img);

   cout << white;

    if (white > 50000)
	cout << "Lost af";
    else if (white < 35000)
	cout << " On Intersection";
    else
	cout << " On Line";

    //int key = cv::waitKey(30) & 255; // key is an integer here
    //if (key == 27) break;    
   // }
}
