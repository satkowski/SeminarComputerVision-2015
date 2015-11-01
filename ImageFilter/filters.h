#ifndef FILTERS_H
#define FILTERS_H

#include <set>
#include <list>
#include "opencv2/imgproc/imgproc.hpp"

cv::Mat unsarpeningFilter(cv::Mat* input);
cv::Mat medianFilter_Threshhold(cv::Mat* input, int threshhold, int windowSize = 1);

#endif // FILTERS_H