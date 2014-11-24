#include "visioninitialization.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;

VisionInitialization::VisionInitialization()
{
    VideoCapture capture(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,120);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,160);
    if(!capture.isOpened())
    {
        cout << "Failed to connect to the camera." <<endl;
    }
    Mat img;
    capture >> img;
    if(img.empty())
    {
        cout << "Failed to capture an image" << endl;
    }
    else
    {
        std::vector<cv::Point2f> srcPoints;
        std::vector<cv::Point2f> dstPoints;

        srcPoints.push_back(Point2f(48,20));
        srcPoints.push_back(Point2f(119,17));
        srcPoints.push_back(Point2f(53,106));
        srcPoints.push_back(Point2f(118,104));
        dstPoints.push_back(Point2f(1,1));
        dstPoints.push_back(Point2f(120,1));
        dstPoints.push_back(Point2f(1,160));
        dstPoints.push_back(Point2f(120,160));
        Mat H;
        Mat img_out = Mat::zeros( img.size(), CV_8UC3 );
        H=cv::findHomography(srcPoints, dstPoints, 0, 3) ;
        warpPerspective(img, img_out, H, img.size(), 1, 1);
        imwrite("warpedOriginal.jpg",img_out);
    }

}
