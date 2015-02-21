cv::SimpleBlobDetector::Params params;
params.minDistBetweenBlobs = 50.0f;
params.filterByInertia = false;
params.filterByConvexity = false;
params.filterByColor = false;
params.filterByCircularity = false;
params.filterByArea = true;
params.minArea = 20.0f;
params.maxArea = 500.0f;
// ... any other params you don't want default value

// set up and create the detector using the parameters
cv::SimpleBlobDetector blob_detector(params);

// detect!
vector<cv::KeyPoint> keypoints;
blob_detector.detect(image, keypoints);

// extract the x y coordinates of the keypoints:

for (int i=0; i<keypoints.size(); i++){
    float X = keypoints[i].pt.x;
    float Y = keypoints[i].pt.y;
}
