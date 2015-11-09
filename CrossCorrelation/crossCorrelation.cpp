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

    Point range = Point(templateImage->cols / 1.5, templateImage->rows / 1.5);
    int windowCounterX = 0;
    double zeroDouble = 0.0;
    double* actualMax = &zeroDouble;
    for (int cY = 0; cY < output.rows - range.y; cY++)
    {
        // Where should the window in vertical direciton starts
        int startY = cY - range.y + 1;
        startY = startY < 0 ? 0 : startY;

        for (int cX = 0; cX < output.cols - range.x; cX++)
        {
            // Is the new pixel outside the window, dont use it anymore
            if (windowCounterX >= range.x)
            {
                actualMax = &zeroDouble;
                windowCounterX = 0;
            }            
            // Look at the new column at the moved window
            for (int wY = startY; wY <= cY; wY++)
            {
                // Is the new value greater than the max, reset all
                if (windowCounterX == 0 ||
                    output.at<double>(wY, cX) > *actualMax)
                {
                    *actualMax = 0.0;
                    actualMax = &output.at<double>(wY, cX);
                    windowCounterX = -1;
                }
                else
                    output.at<double>(wY, cX) = 0.0;
            }
            // Increment for the windowdidth
            if (windowCounterX == -1)
                windowCounterX = 0;
            windowCounterX++;
        }
        actualMax = &zeroDouble;
    }

#pragma endregion
        
    return output;
}