#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// Main method
int main(int argc, const char** argv);

void mouseListener(int event, int x, int y, int, void* userdata);

#endif // MAIN_H