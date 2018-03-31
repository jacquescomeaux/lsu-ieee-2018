#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <exception>
#include <vector>

//kernel = np.ones((5,5), np.uint8)

int main(int argc, char* argv[]) {
	int Y1 = 117;
	int Y2 = 400;
	int X1 = 195;
	int X2 = 440;

	cv::VideoCapture cam(2);
	if(!cam.isOpened()) return -1;

	std::vector<cv::Point2f> pts1, pts2;

	pts1.push_Back(cv::Point2f(92,0));
	pts1.push_Back(cv::Point2f(148,0));
	pts1.push_Back(cv::Point2f(74,283));
	pts1.push_Back(cv::Point2f(178,283));

	pts2.push_Back(cv::Point2f(74,0));
	pts2.push_Back(cv::Point2f(140,0));
	pts2.push_Back(cv::Point2f(74,283));
	pts2.push_Back(cv::Point2f(140,283));

	while(true) {
		cv::Mat ret, image, img;
		cam >> ret >> image;

		img = image(cv::Rect(X1, Y1, Y2-Y1, X2-X1));
		cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);
		warpPerspective(img, dst, M, img.size());

		cv::Mat output = dst.copy();
		
		cv::cvtColor(dst, dst, CV_BGR2GRAY);
		cv::bilateralFilter(dst, 9, 75, 75);

		cv::Canny(dst, dst, 50, 100);
		
		std::vector<cv::Vec3i> circles;
		cv::HoughCircles(dst, circles, CV_HOUGH_GRADIENT, 2, 300, 100, 200, 40, 55);

		if (!circles.empty()) {
			try {
				for(auto it = circles.begin(); it != circles.end(); it++) {
					cv::Point center(cv::Round(circles[it][0]), cv::Round(circles[it][1]));
					//circle center
					cv::circle(ret, center, circles[it][2], cv::Scalar(0,255,0))
					cv::rectangle(ret, (center.x - 5, center.y - 5), (center.x + 5, center.y));

				}//end for
			}//end try
			catch(exception& e) {
			std::cout << "Exception Thrown" << e.what() << std::endl;
			}
		}//endif !circles.empty
		cv::imshow("output", ret);
		
		if(cv::waitKey(1) == 27) break;
	}//end while(true)
cam.release();
cv::destroyAllWindows();
}
