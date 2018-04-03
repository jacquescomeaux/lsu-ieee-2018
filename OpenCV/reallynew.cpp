#include <std::vector>

double threshold_area_low = 5000;
double threshold_area_high = 17000;

int main() {
  cv::VideoCapture cap(2);
  cv::Mat src, imgHSV, mask, maskOpen, maskFinal, blankImg;
  cap >> src;
  cv::cvtColor(src, imgHSV, CV_BGR2HSV);
  #thresh,binary=cv2.threshold(imgHSV, 170, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
  cv::Mat mask = cv::Mat::zeros(imgHSV.size(), imgHSV.type());
  cv::Mat dst = cv::Mat::zeros(imgHSV.size(), imgHSV.type());
  cv::inRange(imgHSV, cv::Scalar(0, 0, 0), Scalar(179, 255, 180), mask);
  cv::morphologyEx(mask, maskOpen, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
  cv::morphologyEx(mask, maskFinal, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(50, 50)));  
  std::vector<std::vector<cv::Point> > contours, approxes;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(maskFinal, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
  for(auto& cont : contours) {
    double area = cv::contourArea(cont);
    if(area < threshold_area_low || area > threshold_area_high) continue;
    cv::Rect boundingRect(cont);
    if(boundingRect.x > 350 || boundingRect.y > 350) continue;
    blankImg = cv::Mat::zeros(img.size(), img.type());
    double epsilon = 0.02 * cv::arcLength(cont, true);
    std::vector<cv:::Point> approx;
    cv::approxPolyDP(cont, approx, epsilon, true);
    approxes.push_back(approx);
    cv::drawContours(blankImg, approx, -1, cv::Scalar(0,255,0), 1);
    cv::drawContours(img, approx, -1, cv::Scalar(0,255,0), 3);
    cv::cvtColor(blankImg, gray_cont, cv::COLOR_BGR2GRAY);
    cv::dilate(gray_cont, gray_cont, cv::NONE);
    cv::Canny(gray_cont, gray_cont, 50, 150, 7);
    cv::HoughLinesP(gray_cont, 3, np.pi/90, 100, 30, 100);
    dst = Mat::zeros( src.size(), CV_32FC1 );
    cv::cornerHarris(gray_cont, dst, 2, 21, 0.1);
    cv::dilate(dst, dst, cv::NONE);
    //#mark corners on original image
    //img[dst>0.4*dst.max()]=[0,0,255]            
  } 
  cv::imshow("corners", img); 
  cv::waitKey(0);
} 
