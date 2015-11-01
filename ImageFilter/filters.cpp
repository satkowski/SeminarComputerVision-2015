#include "filters.h"

using namespace cv;


Mat unsarpeningFilter(Mat* input)
{
#pragma region Initialization

    Mat tempInput;
    input->convertTo(tempInput, CV_64FC3);
    Mat output = Mat(input->rows, input->cols, CV_64FC3, Vec3d(0,0,0));
    // Write the unsharpening mask
    Mat unscharpeningMask = (Mat_<double>(3, 3) << -1, -2, -1,
                                                   -2, 12, -2,
                                                   -1, -2, -1);

#pragma endregion

#pragma region Calculate filtered image

    // Iterate over the whole image, except the borders
    for (int cY = 1; cY < input->rows - 1; cY++)
        for (int cX = 1; cX < input->cols - 1; cX++)
        {
            // Iterate over the whole filter
            for (int fY = -1; fY <= 1; fY++)
                for (int fX = -1; fX <= 1; fX++)
                    // Add the filter to the specific pixel
                    output.at<Vec3d>(cY - 1, cX - 1) += unscharpeningMask.at<double>(fY + 1, fX + 1) *
                                                        tempInput.at<Vec3d>(cY + fY, cX + fX);
            // Dvide by a constant
            output.at<Vec3d>(cY - 1, cX - 1) /= 3;
        }

#pragma endregion

    // Add input image to the unsharpening mask
    output += tempInput;
    output.convertTo(output, CV_8UC3);

    return output;
}

Mat medianFilter(Mat* input, int threshhold)
{
    return Mat();
}