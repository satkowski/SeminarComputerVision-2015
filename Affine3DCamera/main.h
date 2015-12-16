#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"
#include "calculations.h"

#include "opencv2/highgui/highgui.hpp"

// Main method
int main(int argc, const char** argv);

static void onTrackbarCam(int, void* userdate);
static void onTrackbarAff(int, void* userdata);

#endif // MAIN_H