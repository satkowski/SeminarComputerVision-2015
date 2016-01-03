#ifndef COLOREDPOINTCLOUD_H
#define COLOREDPOINTCLOUD_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonDefines.h"

#include <cstdlib>
#include <iostream>

cv::Mat createColoredPointCloudImage(cv::Mat* image, cv::Mat* disparity);

#endif // COLOREDPOINTCLOUD_H
