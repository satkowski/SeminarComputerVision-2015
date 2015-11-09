#ifndef CROSSCORRELATION_H
#define CROSSCORRELATION_H

#include "opencv2/imgproc/imgproc.hpp"

// Find the cross correlation between two images
cv::Mat crossCorrelation(cv::Mat* inputImage, cv::Mat* templateImage);

#endif // CROSSCORRELATION_H