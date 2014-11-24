#include "vision.h"
#include <iostream>
#include <algorithm>

cv::RNG rng(12345);

using namespace std;
using namespace cv;
Vision::Vision()
{
}

void Vision::imgCapture(int condition)
{
    VideoCapture capture(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,1280);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);
    if(!capture.isOpened())
    {
        cout << "Failed to connect to the camera." << endl;
    }
    if(condition==0)
    {
        //Mat img;
        capture >> img;
        if(img.empty())
        {
        cout << "Failed to capture an image" << endl;
        }
        else
            imwrite("Original.jpg",img);
    }
    else
    {
        //Mat imgNew;
        capture >> imgNew;
        if(imgNew.empty())
        {
        cout << "Failed to capture an image" << endl;
        }
        else
            imwrite("New.jpg",imgNew);
    }


}
//cv::Mat img, cv::Mat imgNew, std::vector<cv::Point2f> centroids, cv::Mat1i ind
void Vision::compute()
{
    vector <Point2f> srcPoints;
    vector <Point2f> dstPoints;

    /*srcPoints.push_back(Point2f(48,20));
    srcPoints.push_back(Point2f(119,17));
    srcPoints.push_back(Point2f(53,106));
    srcPoints.push_back(Point2f(118,104));*/
    srcPoints.push_back(Point2f(394,50));
    srcPoints.push_back(Point2f(953,12));
    srcPoints.push_back(Point2f(436,706));
    srcPoints.push_back(Point2f(950,699));
    dstPoints.push_back(Point2f(1,1));
    dstPoints.push_back(Point2f(640,1));
    dstPoints.push_back(Point2f(1,640));
    dstPoints.push_back(Point2f(640,640));

    Mat H;
    //Mat img_out = Mat::zeros( img.size(), CV_8UC3 );
    H=findHomography(srcPoints, dstPoints, 0, 3) ;
    //warpPerspective(img, img_out, H, img.size(), 1, 1);
    //imwrite("warpedoriginal.jpg",img_out);
    //Mat imgNew;
    //imgNew=imread("/home/ubuntu/vision/openCV_Learning/Learning3/PR4/New.jpg",1);
    cout<<"Size of the image "<<imgNew.size()<<endl;
    Mat imgNew_out = Mat::zeros( 640, 640, CV_8UC3 );
    //cout<<"Sugandha printing new image"<<endl;
    //imwrite("New.jpg",imgNew);
    warpPerspective(imgNew, imgNew_out, H, imgNew_out.size(), 1, 1);
    Mat img_out = Mat::zeros( 640, 640, CV_8UC3 );
    warpPerspective(img, img_out, H, img_out.size(), 1, 1);
    //imwrite("WarpedNew.jpg", imgNew_out);
    //Mat img_out=imread("warpedOriginal.jpg",1);
    Mat imgChange;
    absdiff(imgNew_out,img_out,imgChange);
    //imshow("Changed Image",imgChange);
    imwrite("BackgroundChange.jpg",imgChange);
    Mat imgGray;
    cvtColor(imgChange, imgGray, COLOR_BGR2GRAY);
    //imshow("Gray Scale Image",imgGray);
    imwrite("GrayScaleImage.jpg",imgGray);
    Mat imgBw;
    //Otsu thresholding operation
    //threshold( imgGray, imgBw, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU );
    threshold( imgGray, imgBw, 10, 255,cv::THRESH_BINARY);
    //imshow("BW image",imgBw);
    imwrite("BWimage.jpg", imgBw);
   // Mat imgDilute;
   // dilate(imgBw,imgDilute, getStructuringElement(MORPH_ELLIPSE, Size(3,3), Point(-1,-1)));
    Mat imgErode;
    erode(imgBw,imgErode, getStructuringElement(cv::MORPH_ELLIPSE, Size(3,3), Point(-1,-1)));
    cout<<"Size of eroded image is "<<imgErode.size()<<endl;
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
    cout << i<<" Contour area is" << contourArea(contours[i])<<endl ;
    }
   Mat1d size_mat(1, areas.size());
   memcpy(size_mat.data,areas.data(),areas.size()*sizeof(float));
   cv::sortIdx(size_mat, ind, cv::SORT_EVERY_ROW | cv::SORT_DESCENDING);
   cout<<"Biggest bounding rectangeles"<<ind(0,0)<<endl<<ind(0,1)<<endl;
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
    cout<<"x :"<<centroids.at(ind(0,1)).x<<endl<<"y :"<<centroids.at(ind(0,1)).y<<endl;
    c.x=((430/640)*640-centroids.at(ind(0,1)).x)*(500/(430-185));
    c.y=(centroids.at(ind(0,1)).y-194)*(720/(481-194));
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
    cout<<"x :"<<centroids.at(ind(0,0)).x<<endl<<"y :"<<centroids.at(ind(0,0)).y<<endl;
    c.x=(430-centroids.at(ind(0,0)).x)*(2.04);
    c.y=(centroids.at(ind(0,0)).y-194)*2.51;
    cout<<"Centroid Points are x:"<<c.x<<endl;
    cout<<"Centroid Points are y:"<<c.y<<endl;
    return c;
    //cv::Point2f potatoCentroid;
    //cv::Point2f potatoCentroid((89-centroids.at(ind(0,1)).y)*(25/3), (centroids.at(ind(0,1)).x-46)*7.3);
    //return(potatoCentroid);
}

