#include <opencv2/opencv.hpp>
using namespace cv;

Mat thresh_bernsen(Mat& gray,int ksize,int contrast_limit)
{
    Mat ret = Mat::zeros(gray.size(),gray.type());
    for(int i=0;i<gray.cols;i++ )
    {
        for(int j=0;j<gray.rows;j++ )
        {
            double mn=999,mx=0;
            int ti=0,tj=0;
            int tlx=i-ksize/2;
            int tly=j-ksize/2;
            int brx=i+ksize/2;
            int bry=j+ksize/2;
            if(tlx<0) tlx=0;
            if(tly<0) tly=0;
            if(brx>=gray.cols) brx=gray.cols-1;
            if(bry>=gray.rows) bry=gray.rows-1;

            minMaxIdx(gray(Rect(Point(tlx,tly),Point(brx,bry))),&mn,&mx,0,0);
            /* this does the above
            for(int ik=-ksize/2;ik<=ksize/2;ik++)
            {
                for(int jk=-ksize/2;jk<=ksize/2;jk++)
                {
                    ti=i+ik;
                    tj=j+jk;
                    if(ti>0 && ti<gray.cols && tj>0 && tj<gray.rows)
                    {
                        uchar pix = gray.at<uchar>(tj,ti);
                        if(pix<mn) mn=pix;
                        if(pix>mx) mx=pix;
                    }
                }
            }*/
            int median = 0.5 * (mn+mx);
            if(median<contrast_limit)
            {
                ret.at<uchar>(j,i)=0;
            }else
            {
                uchar pix = gray.at<uchar>(j,i);
                ret.at<uchar>(j,i) = pix>median?255:0;
            }
        }
    }
    return ret;
}
int main()
{
    Mat gray, gray2;

    Mat img = imread("notoken3.png",0);
    Mat img2 = imread("token1.png", 0);
    Rect roi;
    roi.x = 200; roi.y = 200; roi.width = 250; roi.height=250;
    gray = img(roi);
    gray2 = img2(roi);
    //fastNlMeansDenoising(gray, gray, 3, 5, 15);
    //fastNlMeansDenoising(gray2, gray2, 3, 5, 15);
    gray2=255-gray2;
    gray=255-gray;
    Mat adaptthresh,bernsen;
    Mat adaptthresh2,bernsen2;
    //bilateralFilter(gray, gray, 9, 75, 75);
    //bilateralFilter(gray2,gray2,9, 75, 75);
    adaptiveThreshold(gray2,adaptthresh2,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,41,1);
    adaptiveThreshold(gray,adaptthresh,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,41,1);
    bernsen2=thresh_bernsen(gray2,25,40);
    bernsen=thresh_bernsen(gray,25,40);
    //imwrite("gray",gray);
    imshow("ThreshhNone.png",adaptthresh);
    imshow("BersennNone.png",bernsen);
    imshow("Threshh.png", adaptthresh2);
    imshow("Bersenn.png", bernsen2);
    waitKey(0);
}
