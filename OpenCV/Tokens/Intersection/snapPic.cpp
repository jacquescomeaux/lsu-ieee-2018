#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../../../RobotSource/include/Camera.h"

int main(int argc, char** argv)
{
  Camera cam(2);

  cv::Mat image, img;

  cam >> image;

  img = image(cv::Rect(195,150,245,283));

  cv::imwrite("Inter.png", img);
}
