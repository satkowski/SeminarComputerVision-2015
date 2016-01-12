#include "postProcessing.h"

using namespace cv;

void postProccesing(Mat* firstDisparity, Mat* secondDisparity)
{
#pragma region Median

    medianFilterInt(firstDisparity);
    medianFilterInt(secondDisparity);

#pragma endregion

#pragma region Left-right-consistency

    int unequal = 0;
    for (int cY = 0; cY < firstDisparity->rows; cY++)
        for (int cX = 0; cX < firstDisparity->cols; cX++)
        {
            int firstPosition = cX + -firstDisparity->at<int>(cY, cX);
            int secondPosition = firstPosition + secondDisparity->at<int>(cY, firstPosition);

            if (secondPosition != cX)
                unequal++;
        }
    std::cout << "failure rate: " << (float)unequal / (firstDisparity->rows * firstDisparity->cols) << std::endl;

#pragma endregion

#pragma region Occlusion

    std::vector<Point2i> firstOcclusion, secondOcclusion;
    for (int cY = 0; cY < firstDisparity->rows; cY++)
        for (int cX = 0; cX < firstDisparity->cols; cX++)
        {
            int firstPosition = cX + -firstDisparity->at<int>(cY, cX);
            int secondPosition = firstPosition + secondDisparity->at<int>(cY, firstPosition);

            if (abs(secondPosition - cX) > OCCLUSION_MAX_DIFFERENCE)
                firstOcclusion.push_back(Point2i(cX, cY));

            firstPosition = cX + secondDisparity->at<int>(cY, cX);
            secondPosition = firstPosition + -firstDisparity->at<int>(cY, firstPosition);

            if (abs(secondPosition - cX) > OCCLUSION_MAX_DIFFERENCE)
                secondOcclusion.push_back(Point2i(cX, cY));
        }

#pragma endregion
    
    firstDisparity->convertTo(*firstDisparity, CV_8U);
    secondDisparity->convertTo(*secondDisparity, CV_8U);
}

void medianFilterInt(Mat* image)
{
    if (image->type() != CV_32S)
        return;

    Mat medianImage = Mat(image->rows, image->cols, CV_32S, Scalar(0));
    for (int cY = MEDIANSIZE; cY < image->rows - MEDIANSIZE; cY++)
        for (int cX = MEDIANSIZE; cX < image->cols - MEDIANSIZE; cX++)
        {
            std::vector<int> pixelVector;
            for (int wY = cY - MEDIANSIZE; wY <= cY + MEDIANSIZE; wY++)
                for (int wX = cX - MEDIANSIZE; wX <= cX + MEDIANSIZE; wX++)
                    pixelVector.push_back(image->at<int>(wY, wX));

            std::sort(pixelVector.begin(), pixelVector.end());
            medianImage.at<int>(cY, cX) = pixelVector.at(pixelVector.size() / 2);
        }

    *image = medianImage;
}