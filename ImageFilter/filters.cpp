#include "filters.h"

using namespace cv;


Mat unsarpeningFilter(Mat* input)
{
#pragma region Initialization

    Mat tempInput;
    input->convertTo(tempInput, CV_64FC3);
    Mat output = Mat(input->rows, input->cols, CV_64FC3, Vec3d(0,0,0));
    // Write the unsharpening mask
    Mat unscharpeningMask = (Mat_<double>(3, 3) << -1, -2, -1,
                                                   -2, 12, -2,
                                                   -1, -2, -1);

#pragma endregion

#pragma region Calculate filtered image

    // Iterate over the whole image, except the borders
    for (int cY = 1; cY < input->rows - 1; cY++)
        for (int cX = 1; cX < input->cols - 1; cX++)
        {
            // Iterate over the whole filter
            for (int fY = -1; fY <= 1; fY++)
                for (int fX = -1; fX <= 1; fX++)
                    // Add the filter to the specific pixel
                    output.at<Vec3d>(cY - 1, cX - 1) += unscharpeningMask.at<double>(fY + 1, fX + 1) *
                                                        tempInput.at<Vec3d>(cY + fY, cX + fX);
            // Dvide by a constant
            output.at<Vec3d>(cY - 1, cX - 1) /= 3;
        }

#pragma endregion

    // Add input image to the unsharpening mask
    output += tempInput;
    output.convertTo(output, CV_8UC3);

    return output;
}

Mat medianFilter_Threshhold(Mat* input, int threshhold, int windowSize)
{
    // If the windowsize is to low show the original image
    if (windowSize == 0)
        return *input;

#pragma region Initialization

    Mat tempInput, output;
    input->convertTo(tempInput, CV_32F);
    tempInput.copyTo(output);

#pragma endregion

#pragma region Search for pixels over threshhold

    std::list<Point> pixelsOverThreshhold;
    Mat avaibleMat = Mat_<bool>(input->rows, input->cols, true);
    // Iterate through the whole image
    for (int cY = 1; cY < input->rows; cY++)
        for (int cX = 1; cX < input->cols; cX++)
        {
            // Is the pixel with it left/upper neighbour inside the threshhold
            if (abs(tempInput.at<float>(cY - 1, cX) - tempInput.at<float>(cY, cX)) < threshhold)
            {
                // Is the pixel allready in the list
                if (avaibleMat.at<bool>(cY - 1, cX))
                {
                    pixelsOverThreshhold.push_back(Point(cX, cY - 1));
                    avaibleMat.at<bool>(cY - 1, cX) = false;
                }
                // Is the pixel allready in the list
                if(avaibleMat.at<bool>(cY, cX))
                {
                    pixelsOverThreshhold.push_back(Point(cX, cY));
                    avaibleMat.at<bool>(cY, cX) = false;
                }
            }
            // Is the pixel with it left/upper neighbour inside the threshhold
            if (abs(tempInput.at<float>(cY, cX - 1) - tempInput.at<float>(cY, cX)) < threshhold)
            {
                // Is the pixel allready in the list
                if (avaibleMat.at<bool>(cY, cX - 1))
                {
                    pixelsOverThreshhold.push_back(Point(cX - 1, cY));
                    avaibleMat.at<bool>(cY, cX - 1) = false;
                }
                // Is the pixel allready in the list
                if (avaibleMat.at<bool>(cY, cX))
                {
                    pixelsOverThreshhold.push_back(Point(cX, cY));
                    avaibleMat.at<bool>(cY, cX) = false;
                }
            }
        }

#pragma endregion

#pragma region Use median filter on elements in set

    // Went through all pixel that are less than the threshhold
    for each (Point pixel in pixelsOverThreshhold)
    {
        // Add all neighbour pixels in the windowsize to the set
        std::multiset<float> pixelValues;
        for (int wY = -windowSize; wY <= windowSize; wY++)
            for (int wX = -windowSize; wX <= windowSize; wX++)
            {
                // If the pixel would be outside
                if (pixel.y + wY < 0 || input->rows <= pixel.y + wY ||
                    pixel.x + wX < 0 || input->cols <= pixel.x + wX)
                    continue;
                pixelValues.insert(tempInput.at<float>(pixel.y + wY, pixel.x + wX));
            }
        // Iterate through the list to the median
        std::multiset<float, std::less<float> >::iterator pixelValuesIter = pixelValues.begin();
        std::advance(pixelValuesIter, (pixelValues.size() + 1) / 2);
        // Set the pixel to the median
        output.at<float>(pixel) = *pixelValuesIter;
    }

#pragma endregion
    
    output.convertTo(output, CV_8U);
    return output;
}