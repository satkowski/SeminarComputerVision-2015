#include "opticalFlow.h"

using namespace cv;

Mat calcOpticalFlow(Vec<void*, 5>* userdata)
{
#pragma region Casting of the data

    Mat* firstImage = static_cast<Mat*>(userdata->val[0]);
    Mat* secondImage = static_cast<Mat*>(userdata->val[1]);
    int blockRadius = *static_cast<int*>(userdata->val[2]);
    int matchingCriteria = *static_cast<int*>(userdata->val[3]);
    int maxFlow = *static_cast<int*>(userdata->val[4]);

#pragma endregion

#pragma region Calculate the disparity
    
    Mat outputX = Mat(secondImage->rows, secondImage->cols, CV_32F, Scalar(0.0f));
    Mat outputY = Mat(secondImage->rows, secondImage->cols, CV_32F, Scalar(0.0f));
    for (int cY = blockRadius; cY < firstImage->rows - blockRadius; cY++)
        for (int cX = blockRadius; cX < firstImage->cols - blockRadius; cX++)
        {
#pragma region Create the rectangles

            int blockHeight = 1 + 2 * blockRadius;
            int minX = cX - blockRadius - maxFlow;
            minX = minX < 0 ? 0 : minX;
            int maxX = cX + blockRadius + maxFlow;
            maxX = maxX >= secondImage->cols ? secondImage->cols - 1 : maxX;
            int minY = cY - blockRadius - maxFlow;
            minY = minY < 0 ? 0 : minY;
            int maxY = maxY = cY + blockRadius + maxFlow;
            maxY = maxY >= secondImage->rows ? secondImage->rows - 1 : maxY;
            Rect templateBlock = Rect(cX - blockRadius, cY - blockRadius, 1 + 2 * blockRadius, blockHeight);
            Rect imageBlock = Rect(minX, minY, maxX - minX, maxY - minY);

#pragma endregion

            // Create the line and the block image
            Mat templateFirstI = Mat(*firstImage, templateBlock);
            Mat blockSecondI = Mat(*secondImage, imageBlock);

#pragma region Decide the method

            // Decide which matching should be used
            Mat blockOutput;
            switch (matchingCriteria)
            {
            case 0:
                matchTemplate(blockSecondI, templateFirstI, blockOutput, CV_TM_SQDIFF);
                break;
            case 1:
                blockOutput = absoulteSumDifference(blockSecondI, templateFirstI);
                break;
            case 2:
                matchTemplate(blockSecondI, templateFirstI, blockOutput, CV_TM_CCORR);
                break;
            }

#pragma endregion

#pragma region Calculate the disparity

            Point minLoc, maxLoc, selectedLoc;
            double minValue, maxValue;
            minMaxLoc(blockOutput, &minValue, &maxValue, &minLoc, &maxLoc);

            // Decide which location ist the current best
            if (matchingCriteria == 0 || matchingCriteria == 1)
                selectedLoc = minLoc;
            else if (matchingCriteria == 2)
                selectedLoc = maxLoc;

            outputX.at<float>(cY, cX) = ((imageBlock.x - (cX - blockRadius)) + selectedLoc.x);
            outputY.at<float>(cY, cX) = ((imageBlock.y - (cY - blockRadius)) + selectedLoc.y);

#pragma endregion
        }

#pragma region Calculate HSV and optical flow

    // Calculate the angle and the magnitude of each disparity
    Mat angleMat = Mat(secondImage->rows, secondImage->cols, CV_32F, Scalar(0.0f));
    Mat magnitudeMat = Mat(secondImage->rows, secondImage->cols, CV_32F, Scalar(0.0f));
    cartToPolar(outputX, outputY, magnitudeMat, angleMat, true);

    // Create the hsv vector from the angle and the magnitude
    Mat hsvOutput = Mat(secondImage->rows, secondImage->cols, CV_32FC3, Scalar(0.0f, 0.0f, 0.0f));
    for (int cY = 0; cY < angleMat.rows; cY++)
        for (int cX = 0; cX < angleMat.cols; cX++)
            hsvOutput.at<Vec3f>(cY, cX) = Vec3f(angleMat.at<float>(cY, cX), magnitudeMat.at<float>(cY, cX), 50.0);

    // Convert the color
    Mat rgbOutput;
    cvtColor(hsvOutput, rgbOutput, COLOR_HSV2BGR);

#pragma endregion

    return rgbOutput;
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