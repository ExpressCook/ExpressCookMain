#include "vision.h"
#include <iostream>
#include <algorithm>

cv::RNG rng(12345);

using namespace std;
using namespace cv;
Vision::Vision()
{
    VideoCapture capture(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,120);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,160);
    if(!capture.isOpened()){
    cout << "Failed to connect to the camera." << endl;
    }
    Mat imgNew;
    capture >> imgNew;
    if(imgNew.empty()){
    cout << "Failed to capture an image" << endl;
    //return -1;
    }

    vector <Point2f> srcPoints;
    vector <Point2f> dstPoints;

    srcPoints.push_back(Point2f(48,20));
    srcPoints.push_back(Point2f(119,17));
    srcPoints.push_back(Point2f(53,106));
    srcPoints.push_back(Point2f(118,104));
    dstPoints.push_back(Point2f(1,1));
    dstPoints.push_back(Point2f(120,1));
    dstPoints.push_back(Point2f(1,160));
    dstPoints.push_back(Point2f(120,160));

    Mat H;
    //Mat img_out = Mat::zeros( img.size(), CV_8UC3 );
    H=findHomography(srcPoints, dstPoints, 0, 3) ;
    //warpPerspective(img, img_out, H, img.size(), 1, 1);
    //imwrite("warpedoriginal.jpg",img_out);
    //Mat imgNew;
    //imgNew=imread("/home/ubuntu/vision/openCV_Learning/Learning3/PR4/New.jpg",1);
    Mat imgNew_out = Mat::zeros( imgNew.size(), CV_8UC3 );
    //cout<<"Sugandha printing new image"<<endl;
    //imwrite("New.jpg",imgNew);
    warpPerspective(imgNew, imgNew_out, H, imgNew.size(), 1, 1);
    //imwrite("WarpedNew.jpg", imgNew_out);
    Mat img_out=imread("warpedOriginal.jpg",1);
    Mat imgChange;
    absdiff(imgNew_out,img_out,imgChange);
    //imwrite("BackgroundChange.jpg",imgChange);
    Mat imgGray;
    cvtColor(imgChange, imgGray, COLOR_BGR2GRAY);
    //imwrite("GrayScaleImage.jpg",imgGray);
    Mat imgBw;
    //Otsu thresholding operation
    //threshold( imgGray, imgBw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU );
    threshold( imgGray, imgBw, 10, 255,cv::THRESH_BINARY);
    //imwrite("BWimage.jpg", imgBw);
   // Mat imgDilute;
   // dilate(imgBw,imgDilute, getStructuringElement(MORPH_ELLIPSE, Size(3,3), Point(-1,-1)));
    Mat imgErode;
    erode(imgBw,imgErode, getStructuringElement(cv::MORPH_ELLIPSE, Size(3,3), Point(-1,-1)));
    //imwrite("Erodedimage.jpg", imgErode);
    Mat dst = Mat::zeros(imgErode.rows, imgErode.cols, CV_8UC3);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //cout<<contours.front().front()<<endl;
    findContours( imgErode, contours, hierarchy,
        cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE );
        // iterate through all the top-level contours,
    // draw each connected component with its own random color
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
}
    vector<double> areas;
    //Mat1i ind;
    int num=contours.size();
    cout<<"Number of contours detected is"<<num<<endl;
    //cout<<"Number of contours is"<< contours.size()<<endl;
    //cout<<"Max element is"<<max_element(contours,contours)<<endl;
    for(int i=0;i<num;i++)
    {
    areas.push_back(contourArea(contours[i]));
    // cout << "Contour area is" << contourArea(contours[i])<<endl ;
    }
   Mat1d size_mat(1, areas.size());
   memcpy(size_mat.data,areas.data(),areas.size()*sizeof(float));
   cv::sortIdx(size_mat, ind, cv::SORT_EVERY_ROW | cv::SORT_DESCENDING);
   cout<<"Biggest bounding rectangeles"<<ind(0,1)<<endl<<ind(0,2)<<endl;
    //namedWindow( "Components", 1 );
   //imwrite( "Components.jpg", dst );
   cout<<"Bounding Rectangles"<<endl;
   vector<vector<Point> > contours_poly( contours.size() );
   vector<Rect> boundRect( contours.size() );
   //vector<Point> centroids;

    for( int i = 0; i < contours.size(); i++ )
     { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       /*TL.push_back(boundRect[i].tl());
       BR.push_back(boundRect[i].br());
       Point t=TL.at(i);
       Point b=BR.at(i);*/
       centroids.push_back(Point((boundRect[i].br().x+boundRect[i].tl().x)/2.0,(boundRect[i].br().y+boundRect[i].tl().y)/2));
       //cout<<boundRect[i].tl().x<<"\t"<<boundRect[i].br().x<<endl;
      // cout<<centroids.at(i)<<endl;
     }
   cout<<"Bounding Rectangles ended"<<endl;
     Mat drawing = Mat::zeros( dst.size(), CV_8UC3 );
   for( int i = 0; i< 2; i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       rectangle( drawing, boundRect[ind(0,i)].tl(), boundRect[ind(0,i)].br(), color, 2, 8, 0 );
       circle(drawing, centroids.at(ind(0,i)),2.0,color,-1,8,0);
     }

    // namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
   //imwrite( "Contours.jpg", drawing );
  //Apple=[(89-centerA(2))*(25/3), (centerA(1)-46)*7.3]
   // waitKey();
    //return 0;
}

CentrePoint Vision::AppleCentroid()
{
    CentrePoint c;
    c.x=(89-centroids.at(ind(0,2)).y)*(25/3);
    c.y=(centroids.at(ind(0,2)).x-46)*7.3;
    return c;
    //cv::Point2f appleCentroid;
    //cv::Point2f appleCentroid((89-centroids.at(ind(0,2)).y)*(25/3), (centroids.at(ind(0,2)).x-46)*7.3);
    //float x=appleCentroid.x;
    //float y=appleCentroid.y;
    //float Centr
    //return(appleCentroid);
}

CentrePoint Vision::PotatoCentroid()
{
    CentrePoint c;
    c.x=(89-centroids.at(ind(0,1)).y)*(25/3);
    c.y=(centroids.at(ind(0,1)).x-46)*7.3;
    return c;
    //cv::Point2f potatoCentroid;
    //cv::Point2f potatoCentroid((89-centroids.at(ind(0,1)).y)*(25/3), (centroids.at(ind(0,1)).x-46)*7.3);
    //return(potatoCentroid);
}

