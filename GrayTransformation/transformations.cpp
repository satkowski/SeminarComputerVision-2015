#include "transformations.h"

using namespace cv;

Mat logTransformation(int sliderValue, Mat* input)
{
#pragma region Initialization

    Mat output = Mat(input->rows, input->cols, CV_8U);
    double alpha = sliderValue * SLIDER_ALPHA_COEFFICENT;
    double c = 255 / (log(255 * exp(alpha) - 254));

#pragma endregion

    for (int cY = 0; cY < input->rows; cY++)
        for (int cX = 0; cX < input->cols; cX++)
            output.at<uchar>(cY, cX) = static_cast<uchar>(c * log(1 + (exp(alpha) - 1) * input->at<double>(cY, cX)));

    return output;
}

Mat powerLawTransformation(int sliderValue, Mat* input)
{
#pragma region Initialization

    Mat output = Mat(input->rows, input->cols, CV_8U);
    double gamma = sliderValue * SLIDER_ALPHA_COEFFICENT;
    double c = 255 / pow(255, gamma);

#pragma endregion

    for (int cY = 0; cY < input->rows; cY++)
        for (int cX = 0; cX < input->cols; cX++)
            output.at<uchar>(cY, cX) = c * pow(input->at<double>(cY, cX), gamma);

    return output;
}

Mat ownTransformation(int sliderValue, Mat* input)
{
#pragma region Initialization

    Mat output = Mat(input->rows, input->cols, CV_8U);

#pragma endregion

    for (int cY = 0; cY < input->rows; cY++)
        for (int cX = 0; cX < input->cols; cX++)
            if (input->at<double>(cY, cX) < sliderValue || sliderValue + OWNTRANSFORMATION_OFFSET < input->at<double>(cY, cX))
                output.at<uchar>(cY, cX) = 0;

    return output;
}