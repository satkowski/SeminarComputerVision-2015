#ifndef CROSSCORRELATION_H
#define CROSSCORRELATION_H

#include "opencv2/imgproc/imgproc.hpp"

// Find the cross correlation between two images
cv::Mat crossCorrelation(cv::Mat* inputImage1, cv::Mat* inputImage2);

#endif // CROSSCORRELATION_H