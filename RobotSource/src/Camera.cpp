 #include "../include/Camera.h"
#include <cmath>
#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include <string>

//adding these trying to get ryan's color detection to work...
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc.hpp"

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
  if(countBlack() > 170) {
    std::cout << "Intersection Detected... Blackness:" << countBlack() << std::endl;
    return true;
  }
  else return false;
}

bool Camera::tokenSeen() {
  return true;
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
  return false;
}

std::vector<cv::Vec3f> Camera::getCircle(unsigned int attempts = 1) { //Detects both intersection and token circles
  int Y1 = 150;
  int X1 = 195;
  int X2 = 440;
  unsigned int runcount;

  //double t = cv::getTickCount();
  cv::Mat image, img, canny, gray, grayBI;
  std::vector<cv::Vec3f> circles;
  for(int i = 0; i < 10; i++) cap >> image;
  for(runcount = 0; runcount < attempts; runcount++) {
    cap >> image;
    img = image(cv::Rect(X1, Y1, X2-X1, 283)); //crop
    cv::warpPerspective(img, img, M2, img.size());
    cv::cvtColor(img, gray, CV_BGR2GRAY);
    //cv::bilateralFilter(gray, grayBI, 5, 75, 75);
    cv::GaussianBlur(gray, grayBI, cv::Size(0,0), 4);
    cv::Canny(grayBI, canny, 30, 40);
    cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 65, 60, 85); //60, 85

    if(!circles.empty()) break;
  }

  return circles;
}

Color Camera::getTokenColor() {
  static std::map<Color,std::pair<cv::Vec6d,std::string> > bgrhsv;
  bgrhsv[Color::BLUE] = std::make_pair(cv::Vec6d(82, 52, 12, 93, 207, 85), "Blue");
  bgrhsv[Color::GREEN] = std::make_pair(cv::Vec6d(59, 109, 33, 71, 180, 110), "Green");
  bgrhsv[Color::RED] = std::make_pair(cv::Vec6d(25, 30, 65, 50, 188, 73), "Red");
  bgrhsv[Color::CYAN] = std::make_pair(cv::Vec6d(76, 81, 17, 79, 176, 81), "Cyan");
  bgrhsv[Color::MAGENTA] = std::make_pair(cv::Vec6d(48, 40, 55, 116, 122, 62), "Magenta");
  bgrhsv[Color::YELLOW] = std::make_pair(cv::Vec6d(39, 117, 101, 40, 173, 117), "Yellow");
  bgrhsv[Color::GRAY] = std::make_pair(cv::Vec6d(37, 48, 25, 74, 129, 48), "Gray");
  bgrhsv[Color::NONE] = std::make_pair(cv::Vec6d(29, 24, 25, 110, 54, 31), "None");
  int b, g, r, h, s, v, sum;
  b = g = r = h = s = v = sum = 0;
  cv::Mat src, bgr, hsv;
  cv::Rect roi;
  roi.x = 100;
  roi.y = 100;
  roi.width = 420;
  roi.height = 220;

  for(int i = 0; i < 10; i++) cap >> bgr;
  cap >> bgr;
  cv::imwrite("token.jpg", bgr);
  cv::Mat img = bgr(roi);
  cv::imwrite("crop.jpg", img);
  cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

  for(int i = 0; i < img.cols; ++i) for(int j = 0; j < img.rows; ++j) {
    b += img.at<cv::Vec3b>(j,i)[0]; //format is (y, x): j is y (height), i is x (width)
    g += img.at<cv::Vec3b>(j,i)[1];
    r += img.at<cv::Vec3b>(j,i)[2];
    h += hsv.at<cv::Vec3b>(j,i)[0];
    s += hsv.at<cv::Vec3b>(j,i)[1];
    v += hsv.at<cv::Vec3b>(j,i)[2];
    sum++;
  }
  std::vector<double> avgs; //to hold average values of (B, G, R, H, S, V) for current image
  avgs.push_back(b/sum);
  avgs.push_back(g/sum);
  avgs.push_back(r/sum);
  avgs.push_back(h/sum);
  avgs.push_back(s/sum);
  avgs.push_back(v/sum);
  double diff = 0;
  std::map<Color,double> distances;
  for(auto& kv : bgrhsv) {
    double total = 0;
    for(int j = 0; j < 6; j++) {
      diff = avgs[j] - kv.second.first[j];
      total += diff * diff;
    }
    total = std::sqrt(total);
    distances[kv.first] = total;
  }
  Color tokenColor;
  double min = 700;
  for(auto& kv : distances) if(kv.second < min) {
    min = kv.second;
    tokenColor = kv.first;
  }

  if (tokenColor == Color::BLUE) if(avgs[1] > 70) tokenColor = Color::CYAN;
  else if(tokenColor == Color::CYAN) if(avgs[1] < 70) tokenColor = Color::BLUE;
  

  if(tokenColor == Color::BLUE) std::cout << "Blue Detected" << std::endl;
  else if (tokenColor == Color::CYAN) std::cout << "Cyan Detected" << std::endl;
  else std::cout << bgrhsv[tokenColor].second << " detected" << std::endl;
  std::cout << "(B, G, R): (" << avgs[0] << ", " << avgs[1] << ", " << avgs[2] << ")" << std::endl;
  std::cout << "(H, S, V): (" << avgs[3] << ", " << avgs[4] << ", " << avgs[5] << ")" << std::endl;

  return tokenColor;
}

bool Camera::checkSortingPlate() {
  cv::Mat img;
  for(int i = 0; i < 5; i++) cap >> img;
  cv::imwrite("tokenarmclear.jpg", img);
  return true;
}
