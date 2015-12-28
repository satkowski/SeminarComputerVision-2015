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
            Mat templateFirstI = Mat(*leftImage, block);
            Mat lineSecondI = Mat(*rightImage, line);

#pragma region Decide the method

            // Decide which matching should be used
            Mat lineOutput;
            switch (matchingCriteria)
            {
            case 0:
                matchTemplate(lineSecondI, templateFirstI, lineOutput, CV_TM_SQDIFF);
                break;
            case 1:
                lineOutput = absoulteSumDifference(lineSecondI, templateFirstI);
                break;
            case 2:
                matchTemplate(lineSecondI, templateFirstI, lineOutput, CV_TM_CCORR);
                break;
            }

#pragma endregion

#pragma region Calculate the disparity

            Point minLoc, maxLoc, selectedLoc;
            double minValue, maxValue;
            minMaxLoc(lineOutput, &minValue, &maxValue, &minLoc, &maxLoc);

            if (matchingCriteria == 0 || matchingCriteria == 1)
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

Mat absoulteSumDifference(Mat image, Mat templateImage)
{
    Mat output = Mat(image.rows - templateImage.rows + 1, image.cols - templateImage.cols + 1, CV_32F);
    // Go through all pixels in the image
    for (int iY = 0; iY < output.rows; iY++)
        for (int iX = 0; iX < output.cols; iX++)
        {
            output.at<float>(iY, iX) = 0;
            // Go through all pixels in the template
            for (int tY = 0; tY < templateImage.rows; tY++)
                for (int tX = 0; tX < templateImage.cols; tX++)
                {
                    // Decide if the image is in color or in grey
                    if (image.type() == CV_8U)
                        output.at<float>(iY, iX) += std::abs((float)image.at<uchar>(iY + tY, iX + tX) - (float)templateImage.at<uchar>(tY, tX));
                    else if (image.type() == CV_8UC3)
                        for (int c = 0; c < 3; c++)
                            output.at<float>(iY, iX) += std::abs((float)image.at<Vec3b>(iY + tY, iX + tX).val[c] - (float)templateImage.at<Vec3b>(tY, tX).val[c]);
                }
        }

    return output;
}