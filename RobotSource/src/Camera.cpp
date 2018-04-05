#include "../include/Camera.h"
#include <cmath>
#include <iostream>
#include <exception>
#include <vector>

//adding these trying to get ryan's color detection to work...
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"

/* Approximate values of Blackness for countBlack(Threshold: 120,255)
Corner Intersection (with token)
	Centered: 20,500 +/- 250
	Off-centered: >= 14,000
-----------------------------------------------
Cross Intersection (with token)
	Centered: 16,000 +/- 50
	Off-centered: Min:13,000 || Max: 18,300
-----------------------------------------------
Lines
	Parallel: 9,950 (MAX)
	Perpendicular: 11,950 (MAX)
*/

Camera::Camera(int n) : INCHES_PER_PIXEL(0.006), /*INCHES_PER_PIXEL(0.00839223)*/ cap(n) {
  //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
  std::vector<cv::Point2f> pts_src, pts_dst;
  pts_src.push_back(cv::Point2f(88, 0));
  pts_src.push_back(cv::Point2f(143, 0));
  pts_src.push_back(cv::Point2f(69, 233));
  pts_src.push_back(cv::Point2f(173, 233));
  pts_dst.push_back(cv::Point2f(69, 0));
  pts_dst.push_back(cv::Point2f(139, 0));
  pts_dst.push_back(cv::Point2f(69, 233));
  pts_dst.push_back(cv::Point2f(139, 233));
  M = cv::getPerspectiveTransform(pts_src, pts_dst);
  //for(int i = 0; i < 50; i++) countBlack();
  std::vector<cv::Point2f> pts12, pts22;
  pts12.push_back(cv::Point2f(92,0));
  pts12.push_back(cv::Point2f(148,0));
  pts12.push_back(cv::Point2f(74,283));
  pts12.push_back(cv::Point2f(178,283));
  pts22.push_back(cv::Point2f(74,0));
  pts22.push_back(cv::Point2f(140,0));
  pts22.push_back(cv::Point2f(74,283));
  pts22.push_back(cv::Point2f(140,283));
  M2 = cv::getPerspectiveTransform(pts12, pts22);

}

int Camera::countBlack() {
  double t = (double)cv::getTickCount(); //for measuring performance
  cv::Mat img;
  cap >> img;
  if(img.empty()) return -1;
  cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
  img = img(cv::Rect(200, 165, 235, 233));
  cv::threshold(img, img, 130, 255, cv::THRESH_BINARY_INV);
  warpPerspective(img, img, M, img.size());
  img = img(cv::Rect(10, 0, 180, 170));
  cv::resize(img, img, cv::Size(), 0.1, 0.1);
  int black = cv::countNonZero(img);
  t = ((double)cv::getTickCount() - t)/cv::getTickFrequency(); //num secs to complete function
  //if(t > 1) std::cout << t << " sec\n";
  //std::cout << "Blackness: " << black << std::endl;
  return black;
}

bool Camera::onLine() {
  if(countBlack() > 100) return true;
  else return false;
}

bool Camera::atIntersection() {
  if(countBlack() > 160) {
  //std::cout << "stopped at int with blackness "<< checkvals[0] << " or " << checkvals[1] << std::endl;
    return true;
  }
  else return false;
}

bool Camera::tokenSeen() {
  return true;
  //if(tokenInFrame(2)) return true;
  //else return false;
}

Coord Camera::determineLocation() const {return Coord(0,0);}

bool Camera::getTokenErrors(float* x, float* y) {
  return getTokenErrors(x, y, 1);
}

bool Camera::getTokenErrors(float* x, float*y, int att) {
  static const int xtarget = 75; //prev 105
  static const int ytarget = 150; //prev 120

  std::vector<cv::Vec3f> circles = getCircle(att);
  if(!circles.empty()) {
    float currentx = xtarget - circles[circles.size() - 1][0];
    float currenty = circles[circles.size() - 1][1] - ytarget;
    *x = currentx * INCHES_PER_PIXEL;
    *y = currenty * INCHES_PER_PIXEL;
   std::cout << "getTokenErrors() x:" << *x << "  y:" << *y << std::endl;
    return true;
  }
  //std::cout << "getTokenErrors Returned False" << std::endl;
  return false;
}

std::vector<cv::Vec3f> Camera::getCircle(int attempts = 1) { //Detects both intersection and token circles
  /*static const int Y1 = 150;
  static const int X1 = 195;
  static const int X2 = 440;

  std::vector<cv::Vec3f> circles;
  cv::Mat image, img, filt;
  for(int i = 0; i < attempts; i++) {
    cap >> image;
    img = image(cv::Rect(X1, Y1, X2-X1, 283)); //crop
    cv::cvtColor(img, img, CV_BGR2GRAY );
    cv::warpPerspective(img, img, M2, img.size());
    cv::GaussianBlur(img, filt, cv::Size(0,0), 4);
    cv::Canny(filt, img, 30, 40);
    cv::HoughCircles(img, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 65, 60, 85);
    if(!circles.empty()) std::cout << "Circle Detected" << std::endl;
    if(!circles.empty()) break;
  }
  return circles;
  
  */int Y1 = 150;
  int X1 = 195;
  int X2 = 440;
  unsigned int runcount = 0;
  
  std::vector<cv::Point2f> pts1, pts2;
  
  pts1.push_back(cv::Point2f(92,0));
  pts1.push_back(cv::Point2f(148,0));
  pts1.push_back(cv::Point2f(74,283));
  pts1.push_back(cv::Point2f(178,283));
  
  pts2.push_back(cv::Point2f(74,0));
  pts2.push_back(cv::Point2f(140,0));
  pts2.push_back(cv::Point2f(74,283));
  pts2.push_back(cv::Point2f(140,283));
  
  //double t = cv::getTickCount();
  runcount++;
  cv::Mat image, img;
  for(int i = 0; i < 10; i++) cap >> image;
  //cap >> image;
  img = image(cv::Rect(X1, Y1, X2-X1, 283)); //crop
  cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);
  cv::warpPerspective(img, img, M, img.size());

  cv::Mat canny, canny2;

  cv::Mat gray;
  cv::Mat grayBI;
  /// Convert it to gray
  cv::cvtColor(img, gray, CV_BGR2GRAY);

  //cv::bilateralFilter(gray, grayBI, 5, 75, 75);
  cv::GaussianBlur(gray, grayBI, cv::Size(0,0), 4);
  // compute canny (don't blur with that image quality!!)
  cv::Canny(grayBI, canny, 30, 40); //prev 200, 20
  //cv::namedWindow("canny"); cv::imshow("canny", canny>0);
  //cv::namedWindow("BLUR"); cv::imshow("BLUR", grayBI>0);

  std::vector<cv::Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 65, 60, 85); //60, 85

  /// Draw the circles detected
  /*for( size_t i = 0; i < circles.size(); i++ ) 
  {
      cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      std::cout << "Run: " << runcount <<  "  Circle Center:  X:" << circles[i][0] << "  Y: " << circles[i][1] << std::endl;
      int radius = cvRound(circles[i][2]);
      cv::circle( img, center, 3, cv::Scalar(0,255,255), -1);
      cv::circle( img, center, radius, cv::Scalar(0,0,255), 1 );
  }*/
  return circles;
}

Color Camera::getTokenColor() {
  //arrays for comparing BGR/HSV values (to be filled in)
  static const cv::Vec6d blue = {0, 0, 0, 0, 0, 0};
  static const cv::Vec6d green = {0, 0, 0, 0, 0, 0};
  static const cv::Vec6d red = {0, 0, 0, 0, 0, 0};
  static const cv::Vec6d cyan = {0, 0, 0, 0, 0, 0};
  static const cv::Vec6d magenta = {0, 0, 0, 0, 0, 0};
  static const cv::Vec6d yellow = {0, 0, 0, 0, 0, 0};
  static const cv::Vec6d gray = {0, 0, 0, 0, 0, 0};


  static const std::vector<cv::Vec6d> bgrhsv = {blue, green, red, cyan, magenta, yellow, gray};
  static int b, g, r, h, s, v, sum;

  cv::Mat src, bgr, hsv;
  cv::Rect roi;
  roi.x = 220;
  roi.y = 290;
  roi.width = 220;
  roi.height = 120;

  cap >> src;
  bgr = src(roi);
  cv::cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);

  /*const unsigned char hue_shift = 80; //this is actually saturation shift
  for (int j = 0; j < hsv.rows; j++) {
    for (int i = 0; i < hsv.cols; i++) {
      unsigned char s = hsv.at<cv::Vec3b>(j,i)[1];
      if (s + hue_shift > 255)
        s = 250;
      else
        s = s + hue_shift;
      hsv.at<cv::Vec3b>(j,i)[1] = s;
    }
  }
  cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR); */

  for (int i = 0; i < bgr.rows; i++) {
    for (int j = 0; j < bgr.cols; j++) {
      b = b + bgr.at<cv::Vec3b>(j,i)[0];
      g = g + bgr.at<cv::Vec3b>(j,i)[1];
      r = r + bgr.at<cv::Vec3b>(j,i)[2];
      h = h + hsv.at<cv::Vec3b>(j,i)[0];
      s = s + hsv.at<cv::Vec3b>(j,i)[1];
      v = v + hsv.at<cv::Vec3b>(j,i)[2];
      sum++;
    }
  }

  std::vector<double> avgs; //to hold average values of (B, G, R, H, S, V) for current image
  avgs.push_back(b/sum);
  avgs.push_back(g/sum);
  avgs.push_back(r/sum);
  avgs.push_back(h/sum);
  avgs.push_back(s/sum);
  avgs.push_back(v/sum);
  static double diff;
  static std::vector<double> distance;


  for(unsigned int i = 0; i < bgrhsv.size(); i++) { //find the distance between current value and all colors
    double total = 0;
    for(int j = 0; j < 6; j++) {
      diff = avgs[j] - bgrhsv[i][j];
      total += diff * diff;
    }
    total = std::sqrt(total);
    distance.push_back(total);
  }
  int color = 0;
  double min = distance[0];
  for(unsigned int i = 1; i < distance.size(); i++) {
    if(distance[i] < min) {
      min = distance[i];
      color = i;
    }
  }

  Color tokenColor = Color::NONE;

  switch(color) {
  case 0 :
    tokenColor = Color::BLUE;
    std::cout << "Blue detected" << std::endl;
    break;
  case 1 :
    tokenColor = Color::GREEN;
    std::cout << "Green detected" << std::endl;
    break;
  case 2 :
    tokenColor = Color::RED;
    std::cout << "Red detected" << std::endl;
    break;
  case 3 :
    tokenColor = Color::CYAN;
    std::cout << "Cyan detected" << std::endl;
    break;
  case 4 :
    tokenColor = Color::MAGENTA;
    std::cout << "Magenta detected" << std::endl;
    break;
  case 5 :
    tokenColor = Color::YELLOW;
    std::cout << "Yellow detected" << std::endl;
    break;
  case 6 :
    tokenColor = Color::GRAY;
    std::cout << "Gray detected" << std::endl;
    break;
  default:
    tokenColor = Color::NONE;
    std::cout << "No color detected" << std::endl;
    break;
  }
  std::cout << "(B, G, R): (" << avgs[0] << ", " << avgs[1] << ", " << avgs[2] << ")" << std::endl;
  std::cout << "(H, S, V): (" << avgs[3] << ", " << avgs[4] << ", " << avgs[5] << ")" << std::endl;

  return tokenColor;
}
