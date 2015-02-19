#ifndef VISION_H
#define VISION_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <vector>
#include <algorithm>
#include <list>

struct DetectionResults
{
    int fruitType;
    cv::Point2f topLeft;
    cv::Point2f bottomRight;
    cv::Point2f centroid;
};

class Vision
{

public:

    /*!
      *\brief constructor for Vision class
      *\param
      * */
    Vision();


    /*!
      *\brief Initializes vision system by capturing the image of the drawer
      *\params 0: Original Image Capture
      *\params 1: New Image Capture
      * */
    void init(int);


    /*!
      *\brief Returns the centroid location of fruit selected on GUI
      *\param 0: Potato centroids, 1: Apple Centroid
      *\return a vector containing type, bounding rectanlge and centroid of each fruit detected
      */
    std::vector<DetectionResults> detect();


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
void findDrawContours(cv::Mat);

/*!
 *\brief Function to determine whether fruit is apple or potato
 *\param
 *\return 0:Potato, 1:Apple
 */

int determineFruit(int i);

/*!
 *\brief Converts points in image co-ordinates suitable to co-ordinates for manipulator motion
 *\param the point whose co-ordinates must be converted
 *\return the point with co-ordinates in manipulator frame
 */

cv::Point2f frameConversion(cv::Point2f pt);


    cv:: Mat _img,_imgNew, _imgHSV;
    std::vector<cv::Point2f> _centroids;
    cv::Mat1i _ind;
    int _numApples, _numPotatoes;         // Stores the number of apples found, number of potatoes found.
    std::vector<std::vector<cv::Point2f> > _contours;
    static int _minArea;
};


#endif // VISION_H
