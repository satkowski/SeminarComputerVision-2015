#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonDefines.h"

#include <cstdlib>
#include <iostream>

// Apply all post processing on the disparities
void postProccesing(cv::Mat* firstDisparity, cv::Mat* secondDisparity);
// Use the medianfilter on the disparitys
void medianFilterInt(cv::Mat* image);

#endif // POSTPROCESSING_H
