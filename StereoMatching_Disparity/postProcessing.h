#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonDefines.h"

#include <set>
#include <cstdlib>
#include <iostream>

// Apply all post processing on the disparities
void postProccesing(cv::Mat* firstDisparity, cv::Mat* secondDisparity, int blockRadius);
// Use the medianfilter on the disparitys
void medianFilter_Int(cv::Mat* image);
float getMedian_Float(cv::Mat* mat, cv::Point2i point, int blockRadius);

#endif // POSTPROCESSING_H
