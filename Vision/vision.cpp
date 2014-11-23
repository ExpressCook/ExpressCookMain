#include "vision.h"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
Vision::Vision()
{
    //QCoreApplication a(argc,argv);
      cout<<"Sugandha"<<endl;
       Mat img;
       //img=imread(argv[1],CV_LOAD_IMAGE_COLOR);
       img = imread("/home/sugandha/Desktop/wall-e-wallpaper-wall-e-6412244-1280-10241.jpg",CV_LOAD_IMAGE_COLOR);
       if(! img.data )                              // Check for invalid input
          {
            cout <<  "Could not open or find the image" << std::endl ;
          //return -1;
           }
       imshow("opencvtest",img);
       imwrite("/home/sugandha/Desktop/Tired.jpg",img);
       cout<<"OpenCV RUnning Test";
       waitKey();
       //return a.exec();
}
