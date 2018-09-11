#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/features2d/features2d.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat img = imread("token1.png");
    
    Ptr<MSER> ms = MSER::create();
    vector<vector<Point> > regions;
    vector<cv::Rect> mser_bbox;
    ms->detectRegions(img, regions, mser_bbox);
    
    for (int i = 0; i < regions.size(); i++)
    {
        rectangle(img, mser_bbox[i], CV_RGB(0, 255, 0));  
    }
    
    imshow("mser", img);
    waitKey(0);
    return 0;
}
