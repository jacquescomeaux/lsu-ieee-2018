#include <opencv2/opencv.hpp>

int main() {
  cv::namedWindow("Control", cv::WINDOW_AUTOSIZE);
  cv::VideoCapture cap(0);
  if(!cap.isOpened()) return -1;
  
  int iLowH = 0;
  int iHighH = 179;
  int iLowS = 0;
  int iHighS = 255;
  int iLowV = 0;
  int iHighV = 255;
  
  cvCreateTrackbar("LowH", "Control", &iLowH, 179);
  cvCreateTrackbar("HighH", "Control", &iHighH, 255);
  cvCreateTrackbar("LowS", "Control", &iLowS, 255);
  cvCreateTrackbar("HighS", "Control", &iHighS, 255);
  cvCreateTrackbar("LowV", "Control", &iLowV, 255);
  cvCreateTrackbar("HighV", "Control", &iHighV, 255);

  cv::Mat frame;

  while(true) {
    cap >> frame;
    cv::imshow("Live Video", frame);
    if(cv::waitKey(33) >= 0) break;
    
    bool bSuccess = cap.read(frame);
    if(!bSuccess) break;
    cv::Mat imgHSV;
    cv::cvtColor(frame, imgHSV, cv::COLOR_BGR2HSV);
    cv::Mat imgThresholded;
    cv::inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded);
    cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    cv::imshow("Thresholded Image", imgThresholded);
    cv::imshow("Original", frame);
    if(cv::waitKey(1) == 27) break;
  }

  return 0;
}
