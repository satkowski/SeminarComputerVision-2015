#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonDefines.h"

#include <cstdlib>
#include <iostream>

void postProccesing(cv::Mat* firstDisparity, cv::Mat* secondDisparity);

#endif // POSTPROCESSING_H
