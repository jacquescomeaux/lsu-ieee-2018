bool tokenSeen() {

  cv::Mat image, img, hsvImg, mask;
  cap >> image;
  static const unsigned int upperBound[3] = {64,67,80};
  img = image(cv::Rect(195,150,245,283));
  cv::warpPerspective(img, img, M2, img.size());
  std::vector<cv::Vec3f> circles=getCircle(7);

  if(circles.empty()) return false;
  
  float x = circles[0][0];
  float y = circles[0][1];
  float r = circles[0][2];

  mask = cv::Mat(283, 245, CV_64F, double(0)); //Look here
  cv::circle(img, (x,y), r, (255,255,255), -1);
  cv::Scalar hsvAverage = cv::mean(img, mask);

  float h = hsvAverage[0];
  float s = hsvAverage[1];
  float v = hsvAverage[2];

  if(h <= upperBound[0] && s <= upperBound[1] && v <= upperBound[2]) return true;

  else return false;

}
