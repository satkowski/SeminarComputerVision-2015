#ifndef STEREO_MATCHING
#define STEREO_MATCHING

#include "opencv2/imgproc/imgproc.hpp"

#include <cstdlib>

cv::Mat calcDisparity(cv::Vec<void*, 4>* userdata);

#endif // STEREO_MATCHING
