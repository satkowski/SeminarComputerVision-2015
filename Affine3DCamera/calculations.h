#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "commonDefines.h"

// Calculate the roation matrix for the camera image
void calcRotationMatCamera(void* userdata);
// Calculate the roation matrix for the affine image
void calcRotationMatAffine(void* userdata);

// Fills the userdata vector
void fillingUserdata(cv::Vec<void*, 10>* userdata);
// Method that calculate the image inside the camera
cv::Mat calcCameraImage(void* userdata);
// Method that calculate the camera position
void calcCameraPosition(void* userdata);
// Method that calculate the affine transformation
cv::Mat calcAffineImage(void* userdata);

#endif // CALCULATIONS_H