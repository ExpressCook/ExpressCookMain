#ifndef VISIONIMPROVED_H
#define VISIONIMPROVED_H


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
      *\params 0: Original Image Capture
      *\params 1: New Image Capture
      * */
    void imgCapture(int);


    /*!
      *\brief Does all the other computation
      *\params Nil
      * returns 0 if 0 fruit found
      * returns 1 if 1 fruit found
      * returns 2 if 2 fruit found
      * */
    int compute();


    /*!
      *\brief Returns the centroid location of fruit selected on GUI
      * \param 0: Potato centroids, 1: Apple Centroid
      */
    CentrePoint CalculateCentroid(int);

cv:: Mat img,imgNew;

private:

/*!
     * \brief computes Homography Matrix for transformation
     */
cv::Mat computeHomography();

/*!
     * \brief perform pre-processing operations
     * homography, background subtraction, grayScale conversion, BW conversion and erosion
     */
cv::Mat preProcessing();

/*!
     * \brief finds contours to help in image segmentation
     * \param takes in the pre-processed image as input and returns contours
     */
std::vector<std::vector<cv::Point> > findDrawContours(cv::Mat);


    std::vector<cv::Point2f> centroids;
    cv::Mat1i ind;
    int numApples, numPotatoes;         // Stores the number of apples found, number of potatoes found.

};

#endif // VISIONIMPROVED_H
