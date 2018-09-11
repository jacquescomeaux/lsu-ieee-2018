#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

// Yellow
// Red
// Green
// Blue
// Yellow
// Purple
// Grey

int main(int argc, char** argv) { 
  VideoCapture cam(0);

  int x1 = 220;
  int x2 = 260;
  int y1 = 360;
  int y2 = 520;

  int b = 0;
  int g = 0;
  int r = 0;
  int sum = 0;

  if(!cam.isOpened()) return -1;
  Mat src;
  cap >> src;
  if(src.empty()) return -1;

  for (int i = x1; x1 <= x2; i++) {
	for (int j = y1; y1 < y2; j++) {
		b = b + src[i][j][0];
		g = g + src[i][j][1];
		r = r + src[i][j][2];
		sum++;
	}
  }

  int avB = B/sum;
  int avG = G/sum;
  int avR = R/sum;

  if (avR > 200) {
	if (avG > 200)
		cout << "Yellow";
	if (avG < 100) && (avB < 100):
		cout << "Red";
  } else if (avR < 80) {
	if (avB < 80)
		cout << "Green";
	if (avG < 80)
		cout << "Blue";
	if (avG > 180) and (avB > 180)
		cout << "Cyan";

  } else if (avG < 80) and (avR > 80) {
	cout << "Purple";

  } else if (avG > 80) and (avR > 80) and (avB > 80) {
	cout << "Grey";

  } else cout << "No color found";

