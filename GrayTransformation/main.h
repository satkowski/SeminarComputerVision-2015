#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"
#include "transformations.h"

#include "opencv2/highgui/highgui.hpp"

// Main method
int main(int argc, const char** argv);

// Select what transformation is used
static void onTrackbarChange(int sliderValue, void* userdata);

#endif // MAIN_H