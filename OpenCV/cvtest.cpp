#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

int main() {
  //cv::namedWindow("Control", cv::WINDOW_AUTOSIZE);
/*

# find centroids
ret, labels, stats, centroids = cv2.connectedComponentsWithStats(dst)

# define the criteria to stop and refine the corners
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.001)
corners = cv2.cornerSubPix(gray,np.float32(centroids),(5,5),(-1,-1),criteria)

# Now draw them
res = np.hstack((centroids,corners))
res = np.int0(res)
img[res[:,1],res[:,0]]=[0,0,255]
img[res[:,3],res[:,2]] = [0,255,0]

cv2.imwrite('subpixel5.png',img)
*/  cv::VideoCapture cap(0);
  if(!cap.isOpened()) return -1;
  cv::Mat frame, gray, dst, ret;
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  while(true) {
    cap >> frame;
    cvtColor(frame, gray, CV_RGB2GRAY);
    cv::cornerHarris(gray, dst, 2, 3, 0.04);
    cv::dilate(dst, dst, cv::_InputArray::NONE);
    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc);
    cv::threshold(dst, ret, 0.01 * maxVal, 255, 0);
    minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc);
    if(minVal != maxVal) dst.convertTo(dst, CV_8U, 255.0 / (maxVal - minVal), -255.0 * minVal / (maxVal - minVal));
    /*findContours(bwThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE, cv::Point(0,0));
    mc = cv::Mat::zeros(frame.size(), CV_8UC3);
    drawContours(mc, contours, 0, cv::Scalar(255, 0, 0), 1);
    std::vector<cv::Point> approx;
    double d = 0;
    do {
      d += 1;
      approxPolyDP(contours[0], approx, d, true);
      std::cout << approx.size() << " " << d << std::endl;
    } while (approx.size() > 4);
    contours.push_back(approx);
    drawContours(mc, contours, contours.size() - 1, cv::Scalar(0, 0, 255), 1);
    */cv::imshow("Live Video", dst);
    if(cv::waitKey(33) >= 0) break;
  }

  return 0;
}
