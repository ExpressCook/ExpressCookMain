#ifndef VISION_H
#define VISION_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <vector>
#include <algorithm>


struct CentrePoint
{
    float x;
    float y;
};

class Vision
{

public:

    /*!
      *\brief Initializes the vision algorithm
      *\param
      * */
    Vision();


    /*!
      *\brief Capture the image and stores it
      * \params 0: Original Image Capture
      * \params 1: New Image Capture
      * */
    void imgCapture(int);


    /*!
      *\brief Does all the other computation
      * \params original image, new image, centroid vector
      * */
    void compute();
    //cv::Mat,cv::Mat,std::vector<cv::Point2f>, cv::Mat1i

   /* /*!
      *\brief Returns the centroid location of apple
      *       Is called when Apple is clicked on GUI
      * \param NIL
      */
   // CentrePoint AppleCentroid();



    /*!
      *\brief Returns the centroid location of Potato
      *       Is called when Potato is clicked on GUI
      * \param 0: Potato centroids, 1: Apple Centroid
      */
    CentrePoint CalculateCentroid(int);
cv:: Mat img,imgNew;

private:
    std::vector<cv::Point2f> centroids;
    cv::Mat1i ind;

};

#endif // VISION_H
