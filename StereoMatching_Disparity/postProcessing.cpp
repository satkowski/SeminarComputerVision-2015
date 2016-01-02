#include "postProcessing.h"

using namespace cv;

void postProccesing(Mat* firstDisparity, Mat* secondDisparity)
{
#pragma region Left-right-consistency

    int unequal = 0;
    for (int cY = 0; cY < firstDisparity->rows; cY++)
    {
        for (int cX = 0; cX < firstDisparity->cols; cX++)
        {
            int firstPosition = cX + firstDisparity->at<int>(cY, cX);
            int secondPosition = firstPosition + secondDisparity->at<int>(cY, firstPosition);

            if (secondPosition != cX)
                unequal++;
        }
    }
    std::cout << "failure rate: " << unequal / (firstDisparity->rows * firstDisparity->cols) << std::endl;

#pragma endregion

#pragma region Median

    medianBlur(*firstDisparity, *firstDisparity, MEDIANSIZE);
    medianBlur(*secondDisparity, *secondDisparity, MEDIANSIZE);

#pragma endregion
}