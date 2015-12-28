#ifndef STEREO_MATCHING
#define STEREO_MATCHING

#include "opencv2/imgproc/imgproc.hpp"

#include <cstdlib>

// Calculate the disparity of 2 stereo images
cv::Mat calcDisparity(cv::Vec<void*, 4>* userdata);
// Calculate the absolute sum of difference from an template in an image
cv::Mat absoulteSumDifference(cv::Mat image, cv::Mat templateImage);

#endif // STEREO_MATCHING
