#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"
#include "stereoMatching.h"
#include "postProcessing.h"
#include "coloredPointCloud.h"

#include "opencv2/highgui/highgui.hpp"

// Main method
int main(int argc, const char** argv);

//Find the optimal blocksize for each pixel
cv::Mat findeOptimalBlockSize(cv::Vec<void*, 5>* userdata, cv::Mat* groundTruth);

#endif // MAIN_H