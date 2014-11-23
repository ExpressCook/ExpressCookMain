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
      *\brief Captures the new image and computes centroid of all existing objects in the image
      *\param NIL
      * */
    Vision();


    /*!
      *\brief Returns the centroid location of apple
      *       Is called when Apple is clicked on GUI
      * \param NIL
      */
    CentrePoint AppleCentroid();



    /*!
      *\brief Returns the centroid location of Potato
      *       Is called when Potato is clicked on GUI
      * \param NIL
      */
    CentrePoint PotatoCentroid();

private:
    std::vector<cv::Point2f> centroids;
    cv::Mat1i ind;

};

#endif // VISION_H
