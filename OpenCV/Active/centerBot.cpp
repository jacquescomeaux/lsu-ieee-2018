
#include <iostream>
#include <stdio.h>
#include "opencv2/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
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
  roi.height = 293;

  while (true) {
  /// Read the image
    cap >> src;
    if(src.empty()) return -1;

    Mat crop = src(roi);

    /// Convert it to gray
    cvtColor( crop, src_gray, CV_BGR2GRAY );

 /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", src );

  if ((ch = std::cin.get()) == 27) break;
 }
  //waitKey(0);
  return 0;
}
