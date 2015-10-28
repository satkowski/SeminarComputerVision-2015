#ifndef MAIN_H
#define MAIN_H

#include "commonDefines.h"

#include <iostream>
#include <ctime>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

// Main method
int main(int argc, const char** argv);

// Use log transformation on image
static void logTransformation(int sliderValue, void* image);
// Use power law transformation on image
static void powerLawTransformation(int sliderValue, void* image);
// Use my own transformation
static void ownTransformation(int sliderValue, void* image);

#endif // MAIN_H