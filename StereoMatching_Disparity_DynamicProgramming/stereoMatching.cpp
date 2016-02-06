#include "stereoMatching.h"

using namespace cv;

Mat calcDisparity(Vec<void*, 5>* userdata, bool firstImageLeft)
{
#pragma region Casting of the data

    Mat* firstImage = static_cast<Mat*>(userdata->val[0]);
    Mat* secondImage = static_cast<Mat*>(userdata->val[1]);
    int standardBlockRadius = *static_cast<int*>(userdata->val[2]);
    int matchingCriteria = *static_cast<int*>(userdata->val[3]);
    int maxDisparity = *static_cast<int*>(userdata->val[4]);

#pragma endregion

    bool useStandardBlockSize = false;

#pragma region Calculate the disparity

    int offset = firstImageLeft ? -1 : 1;

    Mat outputImage = Mat(secondImage->rows, secondImage->cols, CV_32S, Scalar(0));
    for (int cY = standardBlockRadius; cY < firstImage->rows - standardBlockRadius; cY++)
        for (int cX = standardBlockRadius; cX < firstImage->cols - standardBlockRadius; cX++)
        {

#pragma region Create the rectangles

            int blockHeight = 1 + 2 * standardBlockRadius;
            int minX = cX - standardBlockRadius - maxDisparity;
            minX = minX < 0 ? 0 : minX;
            int maxX = cX + standardBlockRadius + maxDisparity;
            maxX = maxX >= secondImage->cols ? secondImage->cols - 1 : maxX;
            Rect block = Rect(cX - standardBlockRadius, cY - standardBlockRadius, 1 + 2 * standardBlockRadius, blockHeight);
            Rect line = Rect(minX, cY - standardBlockRadius, maxX - minX, blockHeight);

#pragma endregion

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

            // Decide which location ist the current best
            if (matchingCriteria == 0 || matchingCriteria == 1)
                selectedLoc = minLoc;
            else if (matchingCriteria == 2)
                selectedLoc = maxLoc;

            outputImage.at<int>(cY, cX) = offset * ((line.x - (cX - standardBlockRadius)) + selectedLoc.x);

#pragma endregion
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