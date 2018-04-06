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

  //float x = circles[0][0];
  //float y = circles[0][1];
  //float r = circles[0][2];

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

  float h = hsvAverage[0];
  float s = hsvAverage[1];
  float v = hsvAverage[2];

  //count++;

  if(h <= upperBound[0] && s <= upperBound[1] && v <= upperBound[2]) return true;

  else return false;

  return true;
*/
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
  
  /*std::vector<cv::Point2f> pts1, pts2;
  
  pts1.push_back(cv::Point2f(92,0));
  pts1.push_back(cv::Point2f(148,0));
  pts1.push_back(cv::Point2f(74,283));
  pts1.push_back(cv::Point2f(178,283));
  
  pts2.push_back(cv::Point2f(74,0));
  pts2.push_back(cv::Point2f(140,0));
  pts2.push_back(cv::Point2f(74,283));
  pts2.push_back(cv::Point2f(140,283));
  */
  //double t = cv::getTickCount();
  runcount++;
  cv::Mat image, img;
  for(int i = 0; i < 10; i++) cap >> image;
  //cap >> image;
  img = image(cv::Rect(X1, Y1, X2-X1, 283)); //crop
  //cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);
  cv::warpPerspective(img, img, M2, img.size());

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

  return circles;
}

Color Camera::getTokenColor() {
  static std::map<Color,std::pair<cv::Vec6d,std::string> > bgrhsv;
  bgrhsv[Color::BLUE] = std::make_pair(cv::Vec6d(156, 83, 68, 114, 143, 96), "Blue"); // Prev: (87, 44, 36, 115, 137, 87) 
  bgrhsv[Color::GREEN] = std::make_pair(cv::Vec6d(51, 80, 50, 46, 96, 116), "Green"); // Prev: H:61
  bgrhsv[Color::RED] = std::make_pair(cv::Vec6d(38, 24, 85, 172, 183, 99), "Red");   // Prev: (38, 24, 85, 172, 183, 85)
  bgrhsv[Color::CYAN] = std::make_pair(cv::Vec6d(79, 73, 52, 90, 87, 106), "Cyan");   // Prev: H:99    
  bgrhsv[Color::MAGENTA] = std::make_pair(cv::Vec6d(80, 34, 70, 156, 144, 92), "Magenta"); // Prev: 170  
  bgrhsv[Color::YELLOW] = std::make_pair(cv::Vec6d(69, 92, 95, 29, 92, 115), "Yellow");    // Prev: H:79
  bgrhsv[Color::GRAY] = std::make_pair(cv::Vec6d(46, 35, 30, 105, 86, 55), "Gray");        // Prev: H115     
 // bgrhsv[Color::NONE] = std::make_pair(cv::Vec6d(29, 24, 25, 110, 54, 31), "None");       
  int b, g, r, h, s, v, sum;
  b = g = r = h = s = v = sum = 0;
  cv::Mat src, bgr, hsv;
  cv::Rect roi;
  roi.x = 128;
  roi.y = 200;
  roi.width = 490;
  roi.height = 200;
  
  //for(int i = 0; i < ; i++) cap >> bgr;
  cap >> bgr;
  cv::Mat img = bgr(roi);
  cv::cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);
  
  for(int i = 220; i < 440; i++) for(int j = 290; j < 410; j++) {
    b += bgr.at<cv::Vec3b>(j,i)[0];
    g += bgr.at<cv::Vec3b>(j,i)[1];
    r += bgr.at<cv::Vec3b>(j,i)[2];
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
  std::cout << bgrhsv[tokenColor].second << " detected" << std::endl;
  std::cout << "(B, G, R): (" << avgs[0] << ", " << avgs[1] << ", " << avgs[2] << ")" << std::endl;
  std::cout << "(H, S, V): (" << avgs[3] << ", " << avgs[4] << ", " << avgs[5] << ")" << std::endl;

  return tokenColor;
}
