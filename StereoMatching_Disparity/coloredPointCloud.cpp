#include "coloredPointCloud.h"

using namespace cv;

Mat createColoredPointCloudImage(Mat* image, Mat* disparity)
{
#pragma region Calculate focal length

    float focalLength = DEPTH_OF_OBJECT * disparity->at<int>(OBJECT_POSITION_Y, OBJECT_POSITION_X);
    focalLength /= DISTANCE_BETWEEN_IMAGES;

#pragma endregion

#pragma region Calculate depth of pixels

    Mat pixelDepth = Mat(image->rows, image->cols, CV_32S);
    for (int cY = 0; cY < image->rows; cY++)
    {
        for (int cX = 0; cX < image->cols; cX++)
        {
            float value = focalLength * DISTANCE_BETWEEN_IMAGES;
            int disparityValue = disparity->at<int>(cY, cX);
            if (disparityValue != 0)
                value /= disparityValue;
            else
                value = 0;

            pixelDepth.at<int>(cY, cX) = value;
        }
    }

#pragma endregion

    return Mat();
}