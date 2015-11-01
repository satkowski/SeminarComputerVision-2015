#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"
#include "filters.h"

#include "opencv2/highgui/highgui.hpp"

// Main method
int main(int argc, const char** argv);

// If the threshhold is changed
static void onTrackbarsChange(int, void* userdata);

#endif // MAIN_H