#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  cv::VideoCapture cap(2);
  while(true) {
    cv::Mat src, img, eroded, temp, element;
    cap >> src;
    cv::cvtColor(src, src, CV_BGR2GRAY);
    src = src(cv::Rect(200,165,235,240));
    cv::bilateralFilter(src, img, 10, 250, 250);
    cv::threshold(img, img, 180, 255, cv::THRESH_BINARY_INV); 
    cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
    element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    do {
      cv::erode(img, eroded, element);
      cv::dilate(eroded, temp, element);
      cv::subtract(img, temp, temp);
      cv::bitwise_or(skel, temp, skel);
      eroded.copyTo(img);
    } while(cv::countNonZero(img) != 0);
    std::vector<cv::Vec4i> lines;
    //HoughLinesP(skel, lines, 5, 5*CV_PI/180, 100, 10, 300);
    HoughLinesP(skel, lines, 1, CV_PI/180, 60, 10, 220 );
    //std::vector<cv::Vec2f> lines;
    //HoughLines(skel, lines, 1, CV_PI/180, 100, 0, 0 );
    //cv::Mat test(img.size(), CV_8UC1, cv::Scalar(0));
    cv::cvtColor(skel, skel, CV_GRAY2BGR);
    for(size_t i = 0; i < lines.size(); i++) {
      cv::Vec4i l = lines[i];
      //cv::Vec2f l = lines[i];
      line(skel, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
    }
    cv::imshow("lines", src);
    //cv::imshow("lfines", temp);
    //cv::imshow("l2ines", img);
    cv::imshow("32ines", skel);
//    cv::imshow("wow", test);
    cv::waitKey(0);
  }
}
