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
  //if(t > 1) std::cout << t << " sec\n";
  //std::cout << "Blackness: " << black << std::endl;
  return black;
}

bool Camera::onLine() {
  if(countBlack() > 100) return true;
  else return false;
}

bool Camera::atIntersection(bool check_for_circle) {
  if(check_for_circle) {
    std::cout << "checking for circle:" << std::endl;
    double x, y;
    int seen = 0;
    for(int i = 0; i < 5; i++) if(getTokenErrors(&x, &y)) seen++;
    std::cout << "seen: " << seen << std::endl << std::endl;
    return seen >= 2;
  }
  else {
    //if(countBlack() > 160) return true;
    if(countBlack() > 165) return true;
    else return false;
  }
}

bool Camera::tokenSeen() {
  return true;
  //if(tokenInFrame(2)) return true;
  //else return false;

  //static int count = 0;

  //std::vector<int> compression_params;
  //compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  //compression_params.push_back(9);

  /*cv::Mat image, img, hsvImg, mask;
  cap >> image;
  image = cv::imread("Token.png", CV_LOAD_IMAGE_COLOR);
  static const unsigned int upperBound[3] = {64,67,80};
  img = image(cv::Rect(195,150,245,283));
  cv::cvtColor(img, hsvImg, cv::COLOR_BGR2HSV);
  cv::warpPerspective(hsvImg, hsvImg, M2, hsvImg.size());
  std::vector<cv::Vec3f> circles=getCircle(7);

  if(circles.empty()) return false;

  //double x = circles[0][0];
  //double y = circles[0][1];
  //double r = circles[0][2];

  //const unsigned char hue_shift = 80;

  //for (int j = 0; j < hsv.rows; j++) {
  //  for (int i = 0; i < hsv.cols; i++) {
  //    unsigned char s = hsv.at<Vec3b>(j,i)[1];

  //    if (s + hue_shift > 255)
  //      s = (s + hue_shift) - 255;
  //    else
  //      s = s + hue_shift;

    //  hsv.at<Vec3b>(j,i)[1] = s;
  //  }
  //}

  //std::string imFile = "Inter" + std::to_string(count) + ".png";
  //cv::imwrite(imFile, img, compression_params);

  mask = cv::Mat(283, 245, CV_64F, double(0)); //Look here
  //cv::circle(hsvImg, (x,y), r, (255,255,255), -1);
  cv::Scalar hsvAverage = cv::mean(hsvImg, mask);

  double h = hsvAverage[0];
  double s = hsvAverage[1];
  double v = hsvAverage[2];

  //count++;

  if(h <= upperBound[0] && s <= upperBound[1] && v <= upperBound[2]) return true;

  else return false;

  return true;
*/
}

Coord Camera::determineLocation() const {return Coord(0,0);}

bool Camera::getTokenErrors(double* x, double*y) {
  static const int xtarget = 100;
  static const int ytarget = 110;

  std::vector<cv::Vec3f> circles = getCircles();
  if(!circles.empty()) {
    double currentx = xtarget - circles[circles.size() - 1][0];
    double currenty = circles[circles.size() - 1][1] - ytarget;
    *x = currentx * INCHES_PER_PIXEL;
    *y = currenty * INCHES_PER_PIXEL;
    return true;
  }
  return false;
}

std::vector<cv::Vec3f> Camera::getCircles() { //Detects both intersection and token circles
  static const int X1 = 195;
  static const int X2 = 440;
  static const int Y1 = 150;
  static const int Y2 = 433;

  cv::Mat image, img;
  for(int i = 0; i < 5; i++) cap >> image;
  img = image(cv::Rect(X1, Y1, X2 - X1, Y2 - Y1)); //crop
  cv::warpPerspective(img, img, M2, img.size());

  cv::Mat canny, canny2;
  cv::Mat gray, grayBI;

  cv::cvtColor(img, gray, CV_BGR2GRAY);
  cv::GaussianBlur(gray, grayBI, cv::Size(0,0), 4);
  cv::Canny(grayBI, canny, 30, 40); //prev 200, 20
  std::vector<cv::Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, 300, 50, 65, 60, 85); //60, 85
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
  int sum = 0;
  cv::Mat img, bgr, hsv;
  for(int i = 0; i < 10; i++) cap >> img;
  cv::Rect roi(100, 100, 350, 220);
  bgr = img(roi);
  cv::cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);
  std::vector<double> avgs(6, 0);
  for(int i = 0; i < bgr.cols; i++) for(int j = 0; j < bgr.rows; j++) {
    for(int k = 0; k < 3; k++) avgs[k] += bgr.at<cv::Vec3b>(j, i)[k];
    for(int k = 0; k < 3; k++) avgs[k + 3] += hsv.at<cv::Vec3b>(j, i)[k];
    sum++;
  }
  for(double& s : avgs) s /= sum;
  std::map<Color,double> distances;
  for(auto& kv : bgrhsv) for(int j = 0; j < 6; j++) distances[kv.first] += std::pow(avgs[j] - kv.second.first[j], 2);
  for(auto& kv : bgrhsv) distances[kv.first] = std::sqrt(distances[kv.first]);
  Color token_color;
  double min = 700;
  for(auto& kv : distances) if(kv.second < min) {
    min = kv.second;
    token_color = kv.first;
  }
  if(token_color == Color::BLUE || token_color == Color::CYAN) token_color = (avgs[1] > 70) ? Color::CYAN : Color::BLUE;
  std::cout << bgrhsv[token_color].second << " detected" << std::endl;
  std::cout << "(B, G, R): (" << avgs[0] << ", " << avgs[1] << ", " << avgs[2] << ")" << std::endl;
  std::cout << "(H, S, V): (" << avgs[3] << ", " << avgs[4] << ", " << avgs[5] << ")" << std::endl;
  return token_color;
}
