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

    return Mat();
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