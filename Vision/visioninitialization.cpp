#include "visioninitialization.h"
#include <iostream>
#include <algorithm>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
using namespace cv;

RNG rng(12345);
//Function to create a scale space for laplacian operator
void createScaleSpace()
{

}
int main()
{
    Mat testImg, smoothed, laplace, result;
    int numGaussians=20;
    float Thresh=0.05;
    vector<Mat> gaussians;
    vector<Mat> diffGaussians;
    testImg=imread("./butterfly.jpg",CV_LOAD_IMAGE_GRAYSCALE);
float features[testImg.rows][testImg.cols];
    cout<<testImg.at<uchar>(2,3)<<endl;
    imshow("Test Image", testImg);
    //Compute gaussians at different scales and push the resultant images into a vector
    for(int i=0;i<numGaussians;i++)
    {
      float sigma = exp(log(sqrt(2)) * (float)((i)));
      Mat tmp;
      GaussianBlur(testImg, tmp, Size(ceil(sigma*3)*2+1,ceil(sigma*3)*2+1), sigma);
      gaussians.push_back(tmp);
    }
    //Next, compute difference of gaussians
    for(int i=0;i<numGaussians-1;i++)
    {
      Mat tmp;
      subtract(gaussians.at(i+1),gaussians.at(i), tmp);
      diffGaussians.push_back(tmp);
      //imshow("Laplacian", tmp );
      //waitKey(0);
    }
    //Laplacian(smoothed, laplace, CV_16S, 5);
    //imshow("LOG", laplace);
    //convertScaleAbs(laplace, result, (3+1)*0.25);
    //imshow("Laplacian", result);

   //Next, we try to compute features of interest
    for(int r=2;r<testImg.rows-2;r++)
    {
//cout<<r<<endl;
      for(int c=2;c<testImg.cols-2;c++)
        {
//cout<<c<<endl;
          int ind=1;
          float maxVal=0;
          Mat tmp;
          for(int k=0;k<numGaussians-1;k++)
            {
              //cout<<k<<endl;
              tmp=diffGaussians.at(k);
              //cout<<"sugandha"<<double(tmp.at<uchar>(r,c))<<endl;
              if(double((tmp.at<uchar>(r,c)))>maxVal)
                {
                  maxVal=tmp.at<uchar>(r,c);
                  ind=k;
                }
//cout<<k<<endl;
            }
         if(maxVal>Thresh)
            {
              int count=0;
              for(int x=-2;x<=2;x++)
                {
                  for(int y=-2;y<=2;y++)
                    {
                      //cout<<r+x<<" "<<y+c<<endl;
                      if(double((tmp.at<uchar>(r+x,c+y)))>maxVal)
                      count++;
                    }
                }
              if(count==0)
              {cout<<ind<<endl;features[r][c]=float(exp(log(sqrt(2)) * float(ind)));}
            }
        }
    }
Mat drawing = Mat::zeros( testImg.size(), CV_8UC3 );
for(int r=2;r<testImg.rows-2;r++)
    {
      for(int c=2;c<testImg.cols-2;c++)
        {
          if(features[r][c]>0)
          {//cout<<features[r][c]<<endl;
Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
          circle(testImg, Point(r,c), int(features[r][c]), color, 2, 8, 0);}
        }
    }

//cout<<"sugandhasugandhasugandha"<<endl;
    imshow("blobs",testImg);
    waitKey();
    return 0;
}
