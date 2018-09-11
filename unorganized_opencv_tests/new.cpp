#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  cv::VideoCapture caps[3] = {cv::VideoCapture(0), cv::VideoCapture(1), cv::VideoCapture(2)};
  //while(true) {
  cv::Mat images[3];
  for(int j = 0; j < 3; j++) for(int i = 0; i < 10; i++) caps[j] >> images[j]; 
  cv::imwrite("Image1.jpg", images[0]);
  cv::imwrite("Image2.jpg", images[1]);
  cv::imwrite("Image3.jpg", images[2]);
    //cv::Mat src, img, eroded, temp, element;
    //cap >> src;
    //cv::cvtColor(src, src, CV_BGR2GRAY);
    //img = src(cv::Rect(195,117,245,283));
    //cv::bilateralFilter(src, img, 10, 250, 250);
    /*cv::threshold(src, img, 180, 255, cv::THRESH_BINARY_INV); 
    
    std::vector<cv::Point2f> pts_src, pts_dst;
    pts_src.push_back(cv::Point2f(92, 0));
    pts_src.push_back(cv::Point2f(148, 0));
    pts_src.push_back(cv::Point2f(74, 283));
    pts_src.push_back(cv::Point2f(178, 283));
    pts_dst.push_back(cv::Point2f(74, 0));
    pts_dst.push_back(cv::Point2f(140, 0));
    pts_dst.push_back(cv::Point2f(74, 283));
    pts_dst.push_back(cv::Point2f(140, 283));
    cv::Mat h = cv::getPerspectiveTransform(pts_src, pts_dst);
    warpPerspective(src, img, h, src.size());
   *//* cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
    * 
    element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    do {
      cv::erode(img, eroded, element);
      cv::dilate(eroded, temp, element);
      cv::subtract(img, temp, temp);
      cv::bitwise_or(skel, temp, skel);
      eroded.copyTo(img);
    } while(cv::countNonZero(img) != 0);
    *///std::vector<cv::Vec4i> lines;
    //HoughLinesP(skel, lines, 5, 5*CV_PI/180, 100, 10, 300);
    //HoughLinesP(img, lines, 1, CV_PI/180, 60, 10, 220 );
    //std::vector<cv::Vec2f> lines;
    //HoughLines(skel, lines, 1, CV_PI/180, 100, 0, 0 );
    //cv::Mat test(img.size(), CV_8UC1, cv::Scalar(0));
    /*cv::cvtColor(img, img, CV_GRAY2BGR);
    for(size_t i = 0; i < lines.size(); i++) {
      cv::Vec4i l = lines[i];
      //cv::Vec2f l = lines[i];
      line(img, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
    }*/
    //cv::imshow("lines", src);
    //cv::imshow("lfines", temp);
    //cv::imshow("l2ines", img);
    //cv::imshow("32ines", skel);
//    cv::imshow("wow", test);
    //cv::waitKey(0);
  //}
}
