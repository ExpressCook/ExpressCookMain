
#include "vision.h"
#include <iostream>
#include <algorithm>


#define PI 3.14
cv::RNG rng(12345);

using namespace std;
using namespace cv;

int Vision::_minArea;

Vision::Vision()
{
    _minArea = 9000;
    _numApples=0;
    _numPotatoes=0;
}

void Vision::init()
{
    //Remember that color image is read in the BGR format, not RGB
    VideoCapture capture(0);
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
        resize(_imgNew, _imgNew, Size(640, 360));
        imwrite("Original.jpg",_imgNew);
    }

}

vector<DetectionResults> Vision::detect()
{

    vector<DetectionResults> results;

    //numApples=0;
    //numPotatoes=0;

    //Clear the centroids vector for each subsequent iteration
    _centroids.erase(_centroids.begin(),_centroids.begin()+_centroids.size());

    //Perform all pre-processing tasks on the image
    preProcessing();

    //Find the various s in the image to segment objects and draw them for visualization
    findDrawContours();

    vector<int> validContourIdx;

    for(int i=0;i<_contours.size();i++)
    {
        if(contourArea(_contours[i])>=_minArea)
            validContourIdx.push_back(i);

    }

   vector<vector<Point> > contours_poly( validContourIdx.size() );
   vector<Rect> boundRect( validContourIdx.size() );

    for( int i = 0; i < validContourIdx.size(); i++ )
     {
        DetectionResults tmp;
        approxPolyDP( Mat(_contours[validContourIdx.at(i)]), contours_poly[i], 3, true );
        boundRect[i] = boundingRect( Mat(contours_poly[validContourIdx.at(i)]));
       //cout<<i<<" "<<boundRect[i].br().x<<"  "<<boundRect[i].br().y<<"  "<<boundRect[i].tl().x<<"   "<<boundRect[i].tl().y<<endl;
        tmp.topLeft=frameConversion(boundRect[i].tl());
        tmp.bottomRight=frameConversion(boundRect[i].br());
        tmp.centroid=frameConversion(Point2f((boundRect[i].br().x+boundRect[i].tl().x)/2,(boundRect[i].br().y+boundRect[i].tl().y)/2));
        tmp.fruitType=determineFruit(i);

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

   return results;
}

Mat Vision::computeHomography()
{
    vector <Point2f> srcPoints;
    vector <Point2f> dstPoints;

   // Points used for homography
    srcPoints.push_back(Point2f(394,50));
    srcPoints.push_back(Point2f(953,12));
    srcPoints.push_back(Point2f(436,706));
    srcPoints.push_back(Point2f(950,699));

    dstPoints.push_back(Point2f(1,1));
    dstPoints.push_back(Point2f(640,1));
    dstPoints.push_back(Point2f(1,640));
    dstPoints.push_back(Point2f(640,640));

    Mat H;
    H=findHomography(srcPoints, dstPoints, 0, 3) ;
    return H;
}

void Vision::preProcessing()
{
    //Compute homography matrix for transformation
    Mat H=computeHomography();

    //define the output matrix for transformation to be a black image of same size as input image
    Mat imgNew_out = Mat::zeros( 640, 640, CV_8UC3 );
    //perform homography on new image, showing fruits
    //warpPerspective(_imgNew, imgNew_out, H, imgNew_out.size(), 1, 1);
    //imwrite("WarpedNew.jpg", imgNew_out);
    //Remember to change _imgNew to _imgNew itself during warpPerspective operation

    //Transform img to HSV color space
    cvtColor(_imgNew, _imgHSV, COLOR_BGR2HSV);
    imwrite("HSV.jpg",_imgHSV);

    //Convert image to BW depending on Red channel values only
    Mat imgBW;
    vector<Mat> bgr_planes;
    split( _imgNew, bgr_planes );
    threshold(bgr_planes.at(2), imgBW, 20, 255,cv::THRESH_BINARY );
    imwrite("BWImage.jpg",imgBW);

    //Perform morphological operation of eroding
    erode(imgBW,_imgErode, getStructuringElement(cv::MORPH_ELLIPSE, Size(3,3), Point(-1,-1)));
    imwrite("Erodedimage.jpg", _imgErode);
}

void Vision::findDrawContours()
{

    Mat dst = Mat::zeros(_imgErode.rows, _imgErode.cols, CV_8UC3);
    vector<Vec4i> hierarchy;
    findContours( _imgErode, _contours, hierarchy,cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE );

        // iterate through all the top-level contours and draw each connected component with its own random color
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( dst, _contours, idx, color, CV_FILLED, 8, hierarchy );
    }

    //imwrite( "Components.jpg", dst );

}

int Vision::determineFruit(int i)
{
    double meanH=0.0;
    double meanG=0.0;
    int count=0;
    //int countC=0;
    vector<Point> cont=_contours.at(i);
    for(int X=0;X<_imgHSV.rows;X++)
    {
        for(int Y=0;Y<_imgHSV.cols;Y++)
        {
            int position=pointPolygonTest(cont, Point2f(X,Y), false);
            int Sval=_imgHSV.at<cv::Vec3b>(X,Y)[1];
            int Vval=_imgHSV.at<cv::Vec3b>(X,Y)[2];

            if(position==1 && Sval>50 && Vval>70)
            {
                int Hval=_imgHSV.at<cv::Vec3b>(X,Y)[0];
                //int Rval=imgChange.at<cv::Vec3b>(X,Y)[2];
                //meanG=meanG+Rval;
//                      if((cos((2*Hval*PI)/180)+1)<(cos((160*PI)/180)+1) && (cos((2*Hval*PI)/180)+1)>120)
//                      {
//                          countC++;
//                      }
                meanH=meanH+(cos((2*Hval*PI)/180)+1);  //imgHSV.at<cv::Vec3b>(X,Y)[0];//insert H value;
                count++;
            }
        }
    }
    meanH=meanH/count;
    meanG=meanG/count;
    if(meanH>= 0.82 && meanH<=1.85)
    {
        //numApples=0;
        //cout<<"Potatoes before"<<numPotatoes<<endl;
        _numPotatoes++;
        return 0;
        //cout<<"Potatoes after"<<numPotatoes<<endl;

    }
    else
    {

        //cout<<"Apples before"<<numApples<<endl;
        _numApples++;
        return 1;
        //numPotatoes=0;
        //cout<<"Apples after"<<numApples<<endl;
    }

}

Point2f Vision::frameConversion(Point2f pt)
{
    Point2f tmp;
    tmp.x=(430-pt.x)*(2.04);
    tmp.y=(pt.y-194)*2.51;

    return tmp;
}

void Vision::detectingBlobs()
{

    //Mat imgGray;
    //cvtColor(_img, imgGray, COLOR_BGR2GRAY);
    //imwrite("Gray.jpg", imgGray);

    cv::SimpleBlobDetector::Params params;
    params.minDistBetweenBlobs = 50.0f;
    params.filterByInertia = false;
    params.filterByConvexity = false;
    params.filterByColor = true;
    params.filterByCircularity = false;
    params.filterByArea = false;
    params.minArea = 20.0f;
    params.maxArea = 500.0f;
    // ... any other params you don't want default value

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
    //= drawKeypoints(_img, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS);
    imwrite("Blobs.jpg", imBlobs);
    cout<<"Number of blobs "<<keypoints.size()<<endl;
}
