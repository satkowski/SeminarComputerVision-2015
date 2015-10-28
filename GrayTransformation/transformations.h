#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "commonDefines.h"

#include <iostream>
#include <ctime>
#include "opencv2/imgproc/imgproc.hpp"

// Use log transformation on image
cv::Mat logTransformation(int sliderValue, cv::Mat* input);
// Use power law transformation on image
cv::Mat powerLawTransformation(int sliderValue, cv::Mat* input);
// Use my own transformation
cv::Mat ownTransformation(int sliderValue, cv::Mat* input);

#endif // TRANSFORMATIONS_H