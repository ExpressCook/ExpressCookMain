
#include "visionImproved.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#define PI 3.14
cv::RNG rng(12345);

using namespace std;
using namespace cv;

Vision::Vision()
{
    numApples=0;
    numPotatoes=0;
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

int Vision::compute()
{
    //ofstream myfile;
    numApples=0;
    numPotatoes=0;

    //Clear the centroids vector for each subsequent iteration
    centroids.erase(centroids.begin(),centroids.begin()+centroids.size());

    //Perform all pre-processing tasks on the image
    Mat imgErode=preProcessing();


    //Find the various contours in the image to segment objects and draw them for visualization
    vector<vector<Point> > contours=findDrawContours(imgErode);

    vector<double> areas;
    //Mat1i ind;
    int num=contours.size();
    float maxArea=contourArea(contours[0]);
    int indMax=0;
    for(int i=0;i<num;i++)
    {
        if (contourArea(contours[i])>maxArea)
        {
            maxArea=contourArea(contours[i]);
            indMax=i;
        }
    areas.push_back(contourArea(contours[i]));
    //cout << i<<" Contour area is" << contourArea(contours[i])<<endl ;
    }
    //float secondMaxArea=contourArea(contours[0]);
    float secondMaxArea=-1;
    int secondIndMax=0;
    for(int i=0;i<num;i++)
    {
        if (i!= indMax && contourArea(contours[i])>secondMaxArea)
        {
            secondMaxArea=contourArea(contours[i]);
            secondIndMax=i;
        }
    }
    Mat1d size_mat =Mat1d::zeros(1,areas.size());
   memcpy(size_mat.data,areas.data(),areas.size()*sizeof(float));
   cv::sortIdx(size_mat, ind, cv::SORT_EVERY_ROW | cv::SORT_DESCENDING);
   ind.at<int>(0,0)=indMax;
   ind.at<int>(0,1)=secondIndMax;
   imwrite( "Components.jpg", dst );

   vector<vector<Point> > contours_poly( contours.size() );
   vector<Rect> boundRect( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
     { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       cout<<i<<" "<<boundRect[i].br().x<<"  "<<boundRect[i].br().y<<"  "<<boundRect[i].tl().x<<"   "<<boundRect[i].tl().y<<endl;
       centroids.push_back(Point((boundRect[i].br().x+boundRect[i].tl().x)/2,(boundRect[i].br().y+boundRect[i].tl().y)/2));
     }
     Mat drawing = Mat::zeros( dst.size(), CV_8UC3 );
   for( int i = 0; i< 2; i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       //drawContours( drawing, contours_poly, ind(0,i), color, 1, 8, vector<Vec4i>(), 0, Point() );
       rectangle( drawing, boundRect[ind(0,i)].tl(), boundRect[ind(0,i)].br(), color, 2, 8, 0 );
       circle(drawing, centroids.at(ind(0,i)),2.0,color,-1,8,0);
     }

   imwrite("Contours.jpg", drawing );

   int number;     // Stores the number of fruits found

   // Checking how many fruits exist, by taking minArea to be 9000(experimental value)
   if(maxArea>9000 && secondMaxArea>9000)
   {
       //both the biggest areas are bigger than the threshold
       number=2;
   }
   else if(maxArea>9000 && secondMaxArea<9000)
   {
       //Only the biggest area is bigger than the threshold
       number=1;
   }
   else if(maxArea<9000 && secondMaxArea<9000)
   {
       //Even the biggest area is smaller than the threshold
       number=0;
   }
   //cout<<"number is"<<number;
    // Converting image to HSV space to determine apples vs potatoes
   Mat imgHSV;
   cvtColor(imgChange, imgHSV, COLOR_BGR2HSV);
   imwrite("HSV.jpg",imgHSV);
    // Checking whether the existing fruits are apples/potatoes

  if(number>0)
  {
      for(int iter=1;iter<=number;iter++)
      {
          //cout<<"Iter value"<<iter;
          Point2f pt;
          double meanH=0.0;
          double meanG=0.0;
          //cout<<"Existing H value"<<meanH<<endl;
          int count=0;
          int countC=0;
          vector<Point> cont=contours[ind(0,iter-1)];
          myfile.open("HSVval.txt");
          for(int X=0;X<imgHSV.rows;X++)
          {
              for(int Y=0;Y<imgHSV.cols;Y++)
              {
                  pt.x=Y; pt.y=X;
                  int position=pointPolygonTest(cont, pt, false);
                  int Sval=imgHSV.at<cv::Vec3b>(X,Y)[1];
                  int Vval=imgHSV.at<cv::Vec3b>(X,Y)[2];

                  if(position==1 && Sval>50 && Vval>70)
                  {
                      int Hval=imgHSV.at<cv::Vec3b>(X,Y)[0];
                      int Rval=imgChange.at<cv::Vec3b>(X,Y)[2];
                      meanG=meanG+Rval;
//                      if((cos((2*Hval*PI)/180)+1)<(cos((160*PI)/180)+1) && (cos((2*Hval*PI)/180)+1)>120)
//                      {
//                          countC++;
//                      }
                      myfile<<X<<"\t"<<Y<<"\t"<<Hval<<"\t"<<int(imgHSV.at<cv::Vec3b>(X,Y)[1])<<"\t"<<int(imgHSV.at<cv::Vec3b>(X,Y)[2])<<endl;
                      meanH=meanH+(cos((2*Hval*PI)/180)+1);  //imgHSV.at<cv::Vec3b>(X,Y)[0];//insert H value;
                      count++;
                  }
              }
          }
          myfile.close();
          meanH=meanH/count;
          meanG=meanG/count;
          if(meanH>= 0.82 && meanH<=1.85)
          {
              //numApples=0;
              cout<<"Potatoes before"<<numPotatoes<<endl;
              numPotatoes++;
              cout<<"Potatoes after"<<numPotatoes<<endl;

          }
          else
          {

              cout<<"Apples before"<<numApples<<endl;
              numApples++;
              //numPotatoes=0;
              cout<<"Apples after"<<numApples<<endl;
          }
      }
  }

  return number;
}

CentrePoint Vision::CalculateCentroid(int i)
{
     CentrePoint c;
    //Before returning, check whether fruit asked for is available or not
     cout<<"Potatoes: "<<numPotatoes<<endl<<"Apples: "<<numApples<<endl;
    if(i==0 && numPotatoes==0)
    {
        c.x=-1; c.y=-1;
    }
    else if(i==1 && numApples==0)
    {
        c.x=-1; c.y=-1;
    }
    else
    {
        cout<<"x :"<<centroids.at(ind(0,i)).x<<endl<<"y :"<<centroids.at(ind(0,i)).y<<endl;
        c.x=(430-centroids.at(ind(0,i)).x)*(2.04);
        c.y=(centroids.at(ind(0,i)).y-194)*2.51;
        //cout<<"Centroid Points are x:"<<c.x<<endl;
        //cout<<"Centroid Points are y:"<<c.y<<endl;
    }

    return c;
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

Mat Vision::preProcessing()
{
    //Compute homography matrix for transformation
    Mat H=computeHomography();

    //define the output matrix for transformation to be a black image of same size as input image
    Mat imgNew_out = Mat::zeros( 640, 640, CV_8UC3 );
    //perform homography on new image, showing fruits
    warpPerspective(imgNew, imgNew_out, H, imgNew_out.size(), 1, 1);

    //Similary, repeat for original input image, which only shows drawer background, to be used for background subtraction
    Mat img_out = Mat::zeros( 640, 640, CV_8UC3 );
    warpPerspective(img, img_out, H, img_out.size(), 1, 1);
    //imwrite("WarpedNew.jpg", imgNew_out);

    //Perform background subtraction
    Mat imgChange;
    absdiff(imgNew_out,img_out,imgChange);
    //imwrite("BackgroundChange.jpg",imgChange);

    //Convert image to grayscale
    Mat imgGray;
    cvtColor(imgChange, imgGray, COLOR_BGR2GRAY);
    //imwrite("GrayScaleImage.jpg",imgGray);

    //Threshold gray image into BW image
    Mat imgBw;
    threshold( imgGray, imgBw, 20, 255,cv::THRESH_BINARY); //Threshold=20, for Otsu, use cv::HRESH_BINARY | cv::THRESH_OTSU
    //imwrite("BWimage.jpg", imgBw);

    //Perform morphological operation of eroding
    erode(imgBw,imgErode, getStructuringElement(cv::MORPH_ELLIPSE, Size(3,3), Point(-1,-1)));
    //imwrite("Erodedimage.jpg", imgErode);

    return imgErode;

}
vector<vector<Point> > Vision::findDrawContours(Mat imgErode)
{

    Mat dst = Mat::zeros(imgErode.rows, imgErode.cols, CV_8UC3);
    vector<Vec4i> hierarchy;
    findContours( imgErode, contours, hierarchy,
        cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE );

        // iterate through all the top-level contours and draw each connected component with its own random color
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
    }

    return contours;
}
