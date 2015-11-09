#include "crossCorrelation.h"

using namespace cv;

Mat crossCorrelation(Mat* inputImage, Mat* templateImage)
{
#pragma region Initialization

    Mat output = Mat_<double>(inputImage->rows, inputImage->cols, 0.0);
    Mat tempInputImage, tempTemplateImage;
    inputImage->convertTo(tempInputImage, CV_64F);
    templateImage->convertTo(tempTemplateImage, CV_64F);

#pragma endregion

#pragma region Calculate squared sum of the template

    double squaredSumTemplate = 0;
    // Iterate over the template
    for (int cY = 0; cY < templateImage->rows; cY++)
        for (int cX = 0; cX < templateImage->cols; cX++)
            squaredSumTemplate += tempTemplateImage.at<double>(cY, cX) *
                                  tempTemplateImage.at<double>(cY, cX);
    
#pragma endregion

#pragma region Calculate cross correlation

    // Iterate of the input image with the height and widht of the output
    for (int cY = 0; cY < inputImage->rows - templateImage->rows + 1; cY++)
        for (int cX = 0; cX < inputImage->cols - templateImage->cols + 1; cX++)
        {
            double squaredSumPatch = 0;
            // Iterate over the template
            for (int tY = 0; tY < templateImage->rows; tY++)
                for (int tX = 0; tX < templateImage->cols; tX++)
                {
                    output.at<double>(cY, cX) += tempTemplateImage.at<double>(tY, tX) *
                                                 tempInputImage.at<double>(cY + tY, cX + tX);
                    squaredSumPatch += tempInputImage.at<double>(cY + tY, cX + tX) * 
                                       tempInputImage.at<double>(cY + tY, cX + tX);
                }
            // Calculate the cross correlation
            output.at<double>(cY, cX) /= -1 * sqrt(squaredSumPatch * squaredSumTemplate);
            output.at<double>(cY, cX) += 1;
        }

#pragma endregion

#pragma region Non max suppression

    //// First in the horizontal direction
    //double zeroDouble = 0.0;
    //double* actualMax = &zeroDouble;
    //int actualMaxCounter = 0;
    //for (int cY = 0; cY < output.rows; cY++)
    //    for (int cX = 0; cX < output.cols; cX++)
    //    {
    //        // Is the new pixel outside the window, dont use it anymore
    //        if (actualMaxCounter >= templateImage->cols / 1.5)
    //        {
    //            actualMax = &zeroDouble;
    //            actualMaxCounter = 0;
    //        }
    //        // Is the new value greater than the max, reset all
    //        if (actualMaxCounter == 0 ||
    //            output.at<double>(cY, cX) > *actualMax)
    //        {
    //            *actualMax = 0.0;
    //            actualMax = &output.at<double>(cY, cX);
    //            actualMaxCounter = 0;
    //        }
    //        else
    //            output.at<double>(cY, cX) = 0.0;
    //        actualMaxCounter++;
    //    }

    //// Then in the vertical direction
    //actualMax = &zeroDouble;
    //actualMaxCounter = 0;
    //for (int cX = 0; cX < output.cols; cX++)
    //    for (int cY = 0; cY < output.rows; cY++)
    //    {
    //        // Is the new pixel outside the window, dont use it anymore
    //        if (actualMaxCounter >= templateImage->cols / 1.5)
    //        {
    //            actualMax = &zeroDouble;
    //            actualMaxCounter = 0;
    //        }
    //        // Is the new value greater than the max, reset all
    //        if (actualMaxCounter == 0 ||
    //            output.at<double>(cY, cX) > *actualMax)
    //        {
    //            *actualMax = 0.0;
    //            actualMax = &output.at<double>(cY, cX);
    //            actualMaxCounter = 0;
    //        }
    //        else
    //            output.at<double>(cY, cX) = 0.0;
    //        actualMaxCounter++;
    //    }

#pragma endregion
        
    output.convertTo(output, CV_8U);
    return output;
}