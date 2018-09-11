#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <iostream>

double threshold_area_low = 5000;
double threshold_area_high = 17000;

int main() {
  cv::VideoCapture cap(1);
  cv::Mat src, dst, max_dst, img, edge_img, gray_cont, imgHSV, mask, maskOpen, maskFinal, blankImg;
while(true) {
  cap >> src;
  cv::cvtColor(src, imgHSV, CV_BGR2HSV);
  mask = cv::Mat::zeros(imgHSV.size(), imgHSV.type());
  dst = cv::Mat::zeros(imgHSV.size(), imgHSV.type());
  
  cv::inRange(imgHSV, cv::Scalar(0, 0, 0), cv::Scalar(179, 255, 180), mask);
  cv::morphologyEx(mask, maskOpen, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
  cv::morphologyEx(maskOpen, maskFinal, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(50, 50)));  
  
  std::vector<std::vector<cv::Point> > contours;//, approxes;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(maskFinal, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
  blankImg = cv::Mat::zeros(src.size(), src.type());
  int count = 0;
  for(std::vector<cv::Point> cont : contours) {

    std::cout << "hi" << std::endl;
    double area = cv::contourArea(cont);
    if(area < threshold_area_low || area > threshold_area_high) continue;
    cv::Rect rect = boundingRect(cv::Mat(cont));
    if(rect.x > 300 || rect.y > 350) continue;

    double epsilon = 0.015 * cv::arcLength(cont, true);

    std::vector<cv::Point> approx;
    cv::approxPolyDP(cont, approx, epsilon, true);
   // approxes.push_back(approx);
    
    cv::drawContours(blankImg, approx, -1, cv::Scalar(0,255,0), 1);
    cv::drawContours(src, approx, -1, cv::Scalar(0,255,0), 3);
    
    cv::cvtColor(blankImg, gray_cont, cv::COLOR_BGR2GRAY);
    cv::Canny(gray_cont, edge_img, 100, 200, 3);
    
    dst = cv::Mat::zeros(src.size(), CV_32FC1);
    cv::cornerHarris(gray_cont, dst, 15, 15, 0.04);

    cv::dilate(dst, dst, cv::Mat(), cv::Point(-1,-1), 3);
    cv::dilate(dst, max_dst, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(50, 50)));
    dst = dst * (dst == max_dst);
    count++;
    //#mark corners on original image
    //img[dst>0.4*dst.max()]=[0,0,255]            
  } 
  if(count) {
    cv::imshow("corners", edge_img);
    cv::waitKey(0);
  }
}
} 
