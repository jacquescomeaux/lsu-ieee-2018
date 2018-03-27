#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  cv::VideoCapture cap(0);
  while(true) {
    cv::Mat src, img, eroded, temp, element;
    cap >> img;
    cv::cvtColor(img, img, CV_BGR2GRAY);
    //src = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    //src = cv::imread(argv[1], 1);
    cv::threshold(img, img, 127, 255, cv::THRESH_BINARY); 
    cv::resize(img, img, cv::Size(1280, 700));
    //cv::bilateralFilter(src, img, 12, 250, 250);
    //cv::imshow("lines", img);
    //cv::waitKey(0);
    cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
    element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    do {
      cv::erode(img, eroded, element);
      cv::dilate(eroded, temp, element);
      cv::subtract(img, temp, temp);
      cv::bitwise_or(skel, temp, skel);
      eroded.copyTo(img);
    } while(cv::countNonZero(img) != 0);
    //cv::resize(skel, skel, cv::Size(1280, 700));
    cv::imshow("Skeleton", skel);
    cv::waitKey(0);
    /*Canny(skel, skel, 50, 200, 3);
    std::vector<cv::Vec4i> lines;
    HoughLinesP(skel, lines, 1, CV_PI/180, 50, 50, 10 );
    for(size_t i = 0; i < lines.size(); i++) {
      cv::Vec4i l = lines[i];
      line(skel, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
    }*/
    cv::imshow("lines", skel);
    cv::waitKey(0);
  }
}
