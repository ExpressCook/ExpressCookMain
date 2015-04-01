
#include "vision.h"
#include "color_constancy.hpp"
#include <iostream>
#include <algorithm>
#include <unistd.h>


//#define meanGValue 200
#define minGValue 180
#define maxGValue 255
#define threshValLow 40
#define threshValHigh 160
#define PI 3.14
cv::RNG rng(12345);

using namespace std;
using namespace cv;

int Vision::_minArea;
int Vision::_maxArea;

Vision::Vision()
{
    _minArea = 3000;
    _maxArea = 20000;
    _numApples=0;
    _numPotatoes=0;
}

void Vision::takePicture()
{
    //Remember that color image is read in the BGR format, not RGB
    VideoCapture capture(0);
    sleep(3);

    capture.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);

    if(!capture.isOpened())
    {
        cout << "Failed to connect to the camera." << endl;
    }

    capture >> _imgNew;
    if(_imgNew.empty())
        cout << "Failed to capture an image" << endl;
    else
    {
        //cout<<"Initial Size, rows="<<_imgNew.rows<<" cols="<<_imgNew.cols<<endl;
        imwrite("Before Resizing.jpg", _imgNew);
        resize(_imgNew, _imgNew, Size(640, 360));
        //cout<<"After resizing Size, rows="<<_imgNew.rows<<" cols="<<_imgNew.cols<<endl;
        imwrite("Original.jpg",_imgNew);
    }
}

int Vision::detect()
{
    //clear the old results
    results.clear();

    //Clear the centroids and contours vector for each subsequent iteration
    _centroids.erase(_centroids.begin(),_centroids.begin()+_centroids.size());
    _contours.erase(_contours.begin(),_contours.begin()+_contours.size());

    //Perform all pre-processing tasks on the image
    preProcessing();

    //Find the various s in the image to segment objects and draw them for visualization
    findDrawContours();

    vector<int> validContourIdx;

    for(int i=0;i<_contours.size();i++)
    {
        cout<<contourArea(_contours[i])<<endl;
        if(contourArea(_contours[i])>=_minArea && contourArea(_contours[i])<=_maxArea)
            validContourIdx.push_back(i);
    }

    vector<vector<Point> > contours_poly( validContourIdx.size() );
    vector<Rect> boundRect( validContourIdx.size() );

    for( int i = 0; i < validContourIdx.size(); i++ )
    {
        DetectionResults tmp;
        approxPolyDP( Mat(_contours[validContourIdx.at(i)]), contours_poly[i], 3, true );

        boundRect[i] = boundingRect( Mat(contours_poly[i]));

        tmp.topLeft=frameConversion(boundRect[i].tl());
        tmp.bottomRight=frameConversion(boundRect[i].br());
        tmp.centroid=frameConversion(Point2f((boundRect[i].br().x+boundRect[i].tl().x)/2,(boundRect[i].br().y+boundRect[i].tl().y)/2));
        _centroids.push_back(tmp.centroid);
        tmp.fruitType=determineFruit(validContourIdx.at(i));
       cout<<"Type "<<tmp.fruitType<<endl;

        results.push_back(tmp);
    }

    Mat drawing = Mat::zeros( _imgErode.size(), CV_8UC3 );
    for( int i = 0; i< validContourIdx.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        //drawContours( drawing, contours_poly, ind(0,i), color, 1, 8, vector<Vec4i>(), 0, Point() );
        rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        circle(drawing, _centroids.at(i),2.0,color,-1,8,0);
    }

    imwrite("Contours.jpg", drawing );
    return results.size();
}

vector<DetectionResults>& Vision::getList()
{
    return results;
}

DetectionResults Vision::getFirst(int fruitType)
{
    DetectionResults falseResult;
    falseResult.fruitType = -1;

    if(results.size()==0)
    {
        cout <<"Fail to detect any item" << endl;
        return falseResult;
    }

    for(vector<DetectionResults>::iterator it = results.begin();
        it != results.end(); ++it)
    {
        if(it->fruitType == fruitType)
            return *it;
    }

    cout<<"Fail to find any fruit of type:"<< fruitType << endl;
    return falseResult;
}

Mat Vision::computeHomography()
{
    vector <Point2f> srcPoints;
    vector <Point2f> dstPoints;

    // Points used for homography
    srcPoints.push_back(Point2f(173, 5));
    srcPoints.push_back(Point2f(502, 3));
    srcPoints.push_back(Point2f(200, 350));
    srcPoints.push_back(Point2f(495, 343));

    dstPoints.push_back(Point2f(1,1));
    dstPoints.push_back(Point2f(320,1));
    dstPoints.push_back(Point2f(1,360));
    dstPoints.push_back(Point2f(320,360));

    Mat H;
    H=findHomography(srcPoints, dstPoints, 0, 3) ;
    return H;
}

void Vision::preProcessing()
{

    //Compute homography matrix for transformation
    Mat H=computeHomography();

    //define the output matrix for transformation to be a black image of same size as input image
    Mat imgNew_out = Mat::zeros( 360, 320, CV_8UC3 );
    //Mat imgNew_out = Mat::zeros( 320, 360, CV_8UC3 );

    //perform homography on new image, showing fruits
    warpPerspective(_imgNew, _imgNew, H, imgNew_out.size(), 1, 1);
    cout<<"After Homography, rows="<<_imgNew.rows<<" cols="<<_imgNew.cols<<endl;
    imwrite("WarpedNew.jpg", _imgNew);
    //Remember to change _imgNew to _imgNew itself during warpPerspective operation



    //Mat input;
    //input.create(320,360,CV_8UC(3));
    color_correction::gray_edge b2;
    _imgNew = b2.run(_imgNew,1,0);
    imwrite("AfterGrayEdge.jpg", _imgNew);

    //Mat imgRed;
    vector<Mat> bgr_planes;
    split( _imgNew, bgr_planes );
    threshold(bgr_planes.at(2), _imgRed, 150, 255,cv::THRESH_BINARY );
    imwrite("RedPlane.jpg", _imgRed);

    //Transform img to HSV color space
    cvtColor(_imgNew, _imgHSV, CV_BGR2HSV);
    imwrite("HSV.jpg",_imgHSV);

    //Convert image to BW depending on Red channel values only
    Mat imgBW1, imgBW2;


    vector<Mat> hsv_planes;
    split( _imgHSV, hsv_planes );
    threshold(hsv_planes.at(0), imgBW1, threshValLow, 255,cv::THRESH_BINARY_INV );
    threshold(hsv_planes.at(0), imgBW2, threshValHigh, 255,cv::THRESH_BINARY );
    add(imgBW1, imgBW2, _imgBW);


    imwrite("HuePlane.jpg",hsv_planes.at(1));
    imwrite("BWImage1.jpg",imgBW1);
    imwrite("BWImage2.jpg",imgBW2);

    imwrite("BWImage.jpg",_imgBW);

    //Perform morphological operation of erosion followed by dilation

    erode(_imgBW,_imgErode, getStructuringElement(cv::MORPH_ELLIPSE, Size(5,5), Point(-1,-1)));

    imwrite ("Eroded Image.jpg", _imgErode);
    dilate(_imgErode, _imgDilate, getStructuringElement(cv::MORPH_ELLIPSE, Size(5,5), Point(-1,-1)));

    imwrite("Clean image.jpg", _imgDilate);
}

void Vision::findDrawContours()
{

    Mat dst = Mat::zeros(_imgErode.rows, _imgErode.cols, CV_8UC3);
    vector<Vec4i> hierarchy;
    findContours( _imgRed, _contours, hierarchy,cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE );
    //findContours( _imgDilate, _contours, hierarchy,cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE );

    // iterate through all the top-level contours and draw each connected component with its own random color
    int idx = 0;
    if(!hierarchy.empty())
    {
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            Scalar color( rand()&255, rand()&255, rand()&255 );
            drawContours( dst, _contours, idx, color, CV_FILLED, 8, hierarchy );
        }
    }

    imwrite( "Components.jpg", dst );

}

int Vision::determineFruit(int i)
{
    double meanG = 0.0;
    int count=0;

    vector<Point> cont =_contours.at(i);
    cout<<"Checking Area = "<<contourArea(_contours[i])<<endl;
    cout<<"rows="<<_imgNew.rows<<" cols="<<_imgNew.cols<<endl;
    for(int X=0;X<_imgNew.rows;X++)
    {
        for(int Y=0;Y<_imgNew.rows;Y++)
        {
            int position=pointPolygonTest(cont, Point2f(X,Y), false);
            //uint ttt =  _imgDilate.at<uchar>(X,Y);
            //cout<<"Val = "<<ttt<<endl;

            if(position==1 /*&& _imgHSV.at<cv::Vec3b>(X,Y)[0]<threshValLow && _imgHSV.at<cv::Vec3b>(X,Y)[0]>0*/)
            {

                int Gval=_imgNew.at<cv::Vec3b>(Y,X)[1];
                _imgNew.at<cv::Vec3b>(Y,X)[2] = 255;
                _imgNew.at<cv::Vec3b>(Y,X)[0] = 255;
                _imgNew.at<cv::Vec3b>(Y,X)[1] = 255;
                //cout<<"G value is "<<Gval<<endl;
                //if(Gval<min)
                   // min = Gval;
                meanG=meanG+Gval;
                int Rval=_imgNew.at<cv::Vec3b>(X,Y)[2];
                meanR=meanR+Rval;
                int Bval=_imgNew.at<cv::Vec3b>(X,Y)[0];
                meanB=meanB+Bval;
                count++;
            }
        }
    }
imwrite("Contour Modified.jpg", _imgNew);
    //meanH=meanH/count;
    //cout<<"Count is "<<count<<endl;
    //cout<<"Mean Hue Value is "<<meanH<<endl;

    meanG=meanG/count;
    cout<<"Mean G value is "<<meanG<<endl;
    //cout<<"Count is "<<count<<endl;
    //cout<<"Mih H val is "<<min<<endl;

    //if(meanH>= 0.82 && meanH<=1.85)
    //if(min>9.0)
    if(meanG>minGValue)
    {
        _numPotatoes++;
        return 0;

    }
    else
    {
        _numApples++;
        return 1;
    }

}

Point2f Vision::frameConversion(Point2f pt)
{
    Point2f tmp;

    tmp.x=(240-pt.x)*(850/240);
    tmp.y=(pt.y-112)*(720/153);    //original = 132

    return tmp;
}

void Vision::detectingBlobs()
{
    cv::SimpleBlobDetector::Params params;
    params.minDistBetweenBlobs = 50.0f;
    params.filterByInertia = false;
    params.filterByConvexity = false;
    params.filterByColor = true;
    params.filterByCircularity = false;
    params.filterByArea = false;
    params.minArea = 20.0f;
    params.maxArea = 500.0f;

    // set up and create the detector using the parameters
    cv::SimpleBlobDetector blob_detector(params);

    // detect!
    vector<cv::KeyPoint> keypoints;
    blob_detector.detect(_imgNew, keypoints);

    // extract the x y coordinates of the keypoints:

    for (int i=0; i<keypoints.size(); i++){

        float X = keypoints[i].pt.x;
        float Y = keypoints[i].pt.y;
    }

    Mat imBlobs= Mat::zeros( 640, 360, _imgNew.type() );
    drawKeypoints(_imgNew, keypoints, imBlobs, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    imwrite("Blobs.jpg", imBlobs);
    cout<<"Number of blobs "<<keypoints.size()<<endl;
}
