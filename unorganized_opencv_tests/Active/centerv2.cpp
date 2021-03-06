#include "opencv2/features2d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"
//above this is new includes added

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "math.h"

#include <iostream>
#include <exception>
#include <vector>

int main(int argc, char* argv[]) { //argument for num times to check for token. Can run ~5-8 times per second.
  int Y1 = 150;
  int Y2 = 400;
  int X1 = 195;
  int X2 = 440;
  
  cv::VideoCapture cam(1);
  if(!cam.isOpened()) return -1;
  
  std::vector<cv::Point2f> pts1, pts2;
  
  pts1.push_back(cv::Point2f(92,0));
  pts1.push_back(cv::Point2f(148,0));
  pts1.push_back(cv::Point2f(74,283));
  pts1.push_back(cv::Point2f(178,283));
  
  pts2.push_back(cv::Point2f(74,0));
  pts2.push_back(cv::Point2f(140,0));
  pts2.push_back(cv::Point2f(74,283));
  pts2.push_back(cv::Point2f(140,283));
  
  while(true) {
    cv::Mat image, img, dst, dst1;
    cam >> image;
    if(image.empty()) return -1;
    double t = cv::getTickCount();
    img = image(cv::Rect(X1, Y1, X2-X1, 283));
    cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);
    cv::warpPerspective(img, dst, M, img.size());
    cv::warpPerspective(img, img, M, img.size());
    cv::cvtColor(dst, dst1, CV_BGR2GRAY);
    cv::bilateralFilter(dst1, dst, 5, 75, 75);
    cv::Canny(dst, dst, 50, 60);
    std::vector<cv::Vec3f> circles;

    //HoughCircles(input, output, method, dp,
    //minDist - min dist between centers
    //param1 - higher threshold of the 2 passed to Canny() (the lower one is twice smaller)
    //param2 - accumlator threshold for the circle centers at detection stage
    //minRadius - Minimum circle radius
    //maxRadius - Maximum circle radius
    cv::HoughCircles(dst, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 65, 60, 70);
    t = (cv::getTickCount() - t)/cv::getTickFrequency(); //Run Time Per Loop(ms): 120(BEST) - 200(WORST)
    std::cout << "Time: " << t << std::endl;
    try {
      if(!circles.empty()) {
	int x = round(circles[0][0]);
	int y = round(circles[0][1]);
	int radius = round(circles[0][2]);
	cv::Point center(x,y);
	std::cout << "Drawing a Circle at (" << center.x << "," << center.y << ") radius: " << radius << std::endl; 
	cv::circle(img, center, radius, cv::Scalar(0,255,0), 4);
      }
      //else return 0;
    }
    catch(std::exception& e) {
      std::cout << "Exception Thrown" << e.what() << std::endl;
    }
    cv::imshow("output", img); //for debugging
    cv::imshow("dst", dst);
    cv::waitKey(0);
  }//end while(true)
}

