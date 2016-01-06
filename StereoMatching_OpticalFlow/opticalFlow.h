#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonDefines.h"

#include <cstdlib>
#include <iostream>

// Calculate the optical flow o 2 given images
cv::Mat calcOpticalFlow(cv::Vec<void*, 5>* userdata);
// Calculate the absolute sum of difference from an template in an image
cv::Mat absoulteSumDifference(cv::Mat image, cv::Mat templateImage);

#endif // OPTICALFLOW_H
