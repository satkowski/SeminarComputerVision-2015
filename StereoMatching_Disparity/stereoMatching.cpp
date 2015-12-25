#include "stereoMatching.h"

using namespace cv;

Mat calcDisparity(Vec<void*, 4>* userdata)
{
#pragma region Casting of the data

    Mat* leftImage = static_cast<Mat*>(userdata->val[0]);
    Mat* rightImage = static_cast<Mat*>(userdata->val[1]);
    int blockRadius = *static_cast<int*>(userdata->val[2]);
    int matchingCriteria = *static_cast<int*>(userdata->val[3]);

#pragma endregion

#pragma region Calculate the disparity

    // Only use the line of the leftImage and the template of the right image
    Rect block = Rect(0, 0, 1 + 2 * blockRadius, 1 + 2 * blockRadius);
    Rect line = Rect(0, 0, rightImage->cols, 1 + 2 * blockRadius);

    Mat outputImage = Mat(rightImage->rows - 2 * blockRadius, rightImage->cols - 2 * blockRadius, CV_32S);
    for (int cY = blockRadius; cY < leftImage->rows - blockRadius; cY++)
    {
        // Reset the block
        block = Rect(0, block.y, 1 + 2 * blockRadius, block.height);

        for (int cX = blockRadius; cX < leftImage->cols - blockRadius; cX++)
        {
            // Create the line and the block image
            Mat templateLeft = Mat(*leftImage, block);
            Mat lineRight = Mat(*rightImage, line);

#pragma region Decide the method

            // Decide which matching should be used
            Mat lineOutput;
            switch (matchingCriteria)
            {
            case 0:
                matchTemplate(lineRight, templateLeft, lineOutput, CV_TM_SQDIFF);
                break;
            case 1:
                // TODO
                break;
            case 2:
                matchTemplate(lineRight, templateLeft, lineOutput, CV_TM_CCORR);
                break;
            }

#pragma endregion

#pragma region Calculate the disparity

            Point minLoc, maxLoc, selectedLoc;
            double minValue, maxValue;
            minMaxLoc(lineOutput, &minValue, &maxValue, &minLoc, &maxLoc);

            if (matchingCriteria == 0)
                selectedLoc = minLoc;
            else if (matchingCriteria == 2)
                selectedLoc = maxLoc;

            outputImage.at<int>(cY - blockRadius, cX - blockRadius) = std::abs(cX - selectedLoc.x);

#pragma endregion

            block.x++;
        }
        block.y++;
        line.y++;
    }

#pragma endregion

    outputImage.convertTo(outputImage, CV_8U);
    return outputImage;
}