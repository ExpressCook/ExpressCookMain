#ifndef VISION_H
#define VISION_H

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <vector>
#include <algorithm>

class Vision
{

public:
    Vision();
    /*!
      *\brief Captures the new image and computes centroid of all existing objects in the image
      *\param NIL
      * */

    cv::Point2f AppleCentroid();
    /*!
      *\brief Returns the centroid location of apple
      *       Is called when Apple is clicked on GUI
      * \param NIL
      */

    cv::Point2f PotatoCentroid();
    /*!
      *\brief Returns the centroid location of Potato
      *       Is called when Potato is clicked on GUI
      * \param NIL
      */
private:
    std::vector<cv::Point2f> centroids;
    cv::Mat1i ind;

};

#endif // VISION_H
