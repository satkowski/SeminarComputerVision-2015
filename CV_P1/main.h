#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"
#include "multiset.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int argc, const char** argv);

PointVec3fQueue getPriorityQueue(cv::Mat* image);
static void onThreshholdTrackbar(int, void* userdate);

#endif // MAIN_H