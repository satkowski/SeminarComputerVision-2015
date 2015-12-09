#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "commonDefines.h"

void calcRotationMat(void* userdata);

// Fills the userdata vector
void fillingUserdata(cv::Vec<void*, 9>* userdata);
// Method that calculate the image inside the camera
cv::Mat calcCameraImage(void* userdata);
// Method that calculate the camera position
void calcCameraPosition(void* userdata);
// Method that calculate the affine transformation
cv::Mat calcAffineTransformation(void* userdata);

#endif // CALCULATIONS_H