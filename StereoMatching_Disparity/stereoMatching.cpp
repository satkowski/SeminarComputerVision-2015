#include "stereoMatching.h"

using namespace cv;

Mat calcDisparity(Vec<void*, 5>* userdata, Mat* blockRadiusMat, bool firstImageLeft)
{
#pragma region Casting of the data

    Mat* firstImage = static_cast<Mat*>(userdata->val[0]);
    Mat* secondImage = static_cast<Mat*>(userdata->val[1]);
    int standardBlockRadius = *static_cast<int*>(userdata->val[2]);
    int matchingCriteria = *static_cast<int*>(userdata->val[3]);
    int maxDisparity = *static_cast<int*>(userdata->val[4]);

#pragma endregion

    bool useStandardBlockSize = false;
    if (blockRadiusMat == NULL || blockRadiusMat->empty())
        useStandardBlockSize = true;

#pragma region Calculate the disparity

    int offset = firstImageLeft ? -1 : 1;
    // Only use the line of the leftImage and the template of the right image
    Rect block = Rect(0, 0, 1 + 2 * standardBlockRadius, 1 + 2 * standardBlockRadius);
    Rect line = Rect(0, 0, 0, 1 + 2 * standardBlockRadius);
    // The maximal length of the row and the highest possible x value with full length row
    int maxLineLength = maxDisparity * 2 + 1 + standardBlockRadius * 2;
    int maxLineX = secondImage->cols - maxLineLength - 1;

    Mat outputImage = Mat(secondImage->rows, secondImage->cols, CV_32S);
    for (int cY = standardBlockRadius; cY < firstImage->rows - standardBlockRadius; cY++)
    {
        // Reset the rectangles
        block = Rect(0, block.y, 1 + 2 * standardBlockRadius, block.height);
        if(standardBlockRadius * 2 + 1 + maxDisparity > secondImage->cols)
            line = Rect(0, line.y, secondImage->cols, line.height);
        else
            line = Rect(0, line.y, standardBlockRadius * 2 + 1 + maxDisparity, line.height);

        for (int cX = standardBlockRadius; cX < firstImage->cols - standardBlockRadius; cX++)
        {
            // Create the line and the block image
            Mat templateFirstI = Mat(*firstImage, block);
            Mat lineSecondI = Mat(*secondImage, line);

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

            outputImage.at<int>(cY, cX) = offset * ((line.x - (cX - standardBlockRadius)) + selectedLoc.x);

#pragma endregion

            block.x++;
            
#pragma region Increment line rectangle

            // Increment the width till the widht is the max length.
            // -> increment the x position till the x is greater the highest possible x value
            // -> decrement the width and increment the x further
            if (line.width == maxLineLength)
            {
                line.x++;
                if (line.x > maxLineX)
                    line.width--;
            }
            else
            {
                if (line.x == 0)
                    line.width = line.width + 1 > secondImage->cols ? secondImage->cols : line.width + 1;
                else
                {
                    line.x++;
                    line.width--;
                }
            }

#pragma endregion
        }
        block.y++;
        line.y++;
    }

#pragma endregion

    return outputImage;
}

Mat absoulteSumDifference(Mat image, Mat templateImage)
{
#pragma region Image convertion

    if (image.type() == CV_8U)
    {
        image.convertTo(image, CV_32F);
        templateImage.convertTo(templateImage, CV_32F);
    }
    else if (image.type() == CV_8UC3)
    {
        image.convertTo(image, CV_32FC3);
        templateImage.convertTo(templateImage, CV_32F);
    }

#pragma endregion

    Mat output = Mat(image.rows - templateImage.rows + 1, image.cols - templateImage.cols + 1, CV_32F);

    Rect templateRect = Rect(0, 0, templateImage.cols, templateImage.rows);
    // Go through all pixels in the image
    for (int cY = 0; cY < output.rows; cY++)
    {
        for (int cX = 0; cX < output.cols; cX++)
        {
            Mat imageTemplatePart = Mat(image, templateRect);
            // Calculate the absolute difference of the two images and the sum
            Mat absoluteSum;
            absdiff(imageTemplatePart, templateImage, absoluteSum);
            Scalar sumScalar = sum(absoluteSum);

            float totalSum = 0.0f;
            if (image.type() == CV_32F)
                totalSum += sumScalar.val[0];
            else if (image.type() == CV_32FC3)
                for (int c = 0; c < 3; c++)
                    totalSum += sumScalar.val[c];

            output.at<float>(cY, cX) = totalSum;

            templateRect.x++;
        }
        templateRect.y++;
    }

    return output;
}