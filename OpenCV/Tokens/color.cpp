#include <iostream>
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../../RobotSource/include/Color.h"
#include "../../RobotSource/include/Camera.h"
#include "../../RobotSource/include/SortingSystem.h"

using namespace cv;
using namespace std;

/** @function main */
//Color
int main(int argc, char* argv[])
{

  Camera token_cam(0);

  Color tokenColor;

  tokenColor = token_cam.getTokenColor();

  return true;
}
