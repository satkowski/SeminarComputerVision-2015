#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"
#include "helper.h"

#include <list>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// Main method
int main(int argc, const char** argv);

// Calculation of the gradient addition in x and y direction 
cv::Mat getGradientMat(cv::Mat* image);
// Get the list that is sorted by the gradient vector length
std::list<cv::Point> getPriorityList(cv::Mat* gradientMat);

// Method called if the trackbar is changed
static void onThreshholdTrackbar(int, void* userdate);

#endif // MAIN_H