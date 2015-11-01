#ifndef FILTERS_H
#define FILTERS_H

#include "opencv2/imgproc/imgproc.hpp"

cv::Mat unsarpeningFilter(cv::Mat* input);
cv::Mat medianFilter(cv::Mat* input, int threshhold);

#endif // FILTERS_H