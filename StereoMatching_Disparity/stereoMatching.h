#ifndef STEREO_MATCHING_H
#define STEREO_MATCHING_H

#include "opencv2/imgproc/imgproc.hpp"

#include <cstdlib>

// Calculate the disparity of 2 stereo images
std::pair<cv::Mat, int> calcDisparity(cv::Vec<void*, 5>* userdata, bool firstImageLeft);
// Calculate the absolute sum of difference from an template in an image
cv::Mat absoulteSumDifference(cv::Mat image, cv::Mat templateImage);

#endif // STEREO_MATCHING_H
