#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonDefines.h"

#include <set>
#include <cstdlib>
#include <iostream>

// Apply all post processing on the disparities
void postProccesing(cv::Mat* firstDisparity, cv::Mat* secondDisparity, int blockRadius);
// Calculate the left-right-consistency 
void leftRightConsistency(cv::Mat* leftDisparity, cv::Mat* rightDisparity);
// Check accuracy of disparity map with the ground truth disparity
void checkAccuracy(cv::Mat* disparity, cv::Mat* groundTruth);
// Use the medianfilter on the disparitys
void medianFilter_Int(cv::Mat* image);
// Get the median of an image inside of a block around a given point
float getMedian_Float(cv::Mat* mat, cv::Point2i point, int blockRadius);

#endif // POSTPROCESSING_H
