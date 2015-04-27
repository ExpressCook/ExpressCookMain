#ifndef VISION_H
#define VISION_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <vector>
#include <algorithm>
#include <list>
#include <opencv2/nonfree/nonfree.hpp>

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
      *\brief Capturing the image of the drawer
      * */
    void takePicture();

    /*!
      *\brief Detect where the fruit is, and what kind of fruit it is.
      *\return The number of fruits detected
      */
    int detect();

    /*!
     * \brief Return a reference to the entire list of detected fruits
     * \return
     */
    std::vector<DetectionResults>& getList();

    /*!
     * \brief Return the first fruit from the result list
     * \param fruitType 0->potato 1->apple
     * \return
     */
    DetectionResults getFirst(int fruitType);

    /*!
     * \brief number of apples detected
     * \return number of apples detected
     */

    int numOfApples();

    /*!
     * \brief number of potatoes detected
     * \return number of potatoes detected
     */

    int numOfPotatoes();

    /*!
     *\brief Detects blobs by color segmentation
     *\param
     * */
    void detectingBlobs();


private:

    /*!
     * \brief computes Homography Matrix for transformation
     */
    cv::Mat computeHomography();

    /*!
     * \brief perform pre-processing operations
     * homography, background subtraction, grayScale conversion, BW conversion and erosion
     */
    void preProcessing();

    /*!
     * \brief finds contours to help in image segmentation
     * \param takes in the pre-processed image as input and returns contours
     */
    void findDrawContours();

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

    //store the detection results
    std::vector<DetectionResults> results;
    //image matrix for different stages
    cv:: Mat _imgNew, _imgHSV, _imgErode, _imgDilate, _imgBW, _imgRed;
    std::vector<cv::Point2f> _centroids;
    cv::Mat1i _ind;
    // Stores the number of apples found, number of potatoes found.
    int _numApples, _numPotatoes;
    std::vector<std::vector<cv::Point> > _contours;
    static int _minArea;
    static int _maxArea;
};


#endif // VISION_H
