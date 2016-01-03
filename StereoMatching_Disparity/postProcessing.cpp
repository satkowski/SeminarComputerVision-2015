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
            int firstPosition = cX + -firstDisparity->at<int>(cY, cX);
            int secondPosition = firstPosition + secondDisparity->at<int>(cY, firstPosition);

            if (secondPosition != cX)
                unequal++;
        }
    }
    std::cout << "failure rate: " << (float)unequal / (firstDisparity->rows * firstDisparity->cols) << std::endl;

#pragma endregion

    firstDisparity->convertTo(*firstDisparity, CV_8U);
    secondDisparity->convertTo(*secondDisparity, CV_8U);

#pragma region Median

    Mat newFirstDisparity, newSecondDisparity;
    medianBlur(*firstDisparity, newFirstDisparity, MEDIANSIZE);
    medianBlur(*secondDisparity, newSecondDisparity, MEDIANSIZE);

#pragma endregion

    *firstDisparity = newFirstDisparity;
    *secondDisparity = newSecondDisparity;
}