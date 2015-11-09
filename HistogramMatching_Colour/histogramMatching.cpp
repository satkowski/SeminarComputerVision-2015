#include "histogramMatching.h"

using namespace cv;

std::vector<Mat> calcCDFandPDF(Mat* input)
{
#pragma region Initialization

    Mat pdf, cdf;
    float range[2]{ 0, 255 };
    const float* ranges[1]{ range };
    // Values for the Images
    int histSize = 256;
    int histHeight = 400;
    int histWidth = 512;
    int pointWidth = cvRound(static_cast<double>(histWidth) / histSize);

    Mat pdfImage = Mat(histHeight, histWidth, CV_8U, Scalar(0, 0, 0));
    Mat cdfImage = Mat(histHeight, histWidth, CV_8U, Scalar(0, 0, 0));

#pragma endregion

#pragma region Create PDF and CDF

    // Calculate PDF
    calcHist(input, 1, 0, Mat(), pdf, 1, &histSize, ranges, true, false);
    // Plot it
    normalize(pdf, pdf, 0, pdf.rows, NORM_MINMAX, -1, Mat());

    // Calculate CDF
    cdf = Mat(pdf.rows, pdf.cols, CV_32F);
    cdf.at<float>(0) = pdf.at<float>(0);
    for (int cY = 1; cY < cdf.rows; cY++)
        cdf.at<float>(cY) = cdf.at<float>(cY - 1) + pdf.at<float>(cY);
    // Plot it
    normalize(cdf, cdf, 0, pdf.rows, NORM_MINMAX, -1, Mat());

#pragma endregion

#pragma region Draw the PDF- and CDF-image

    // Draw every line between the points for PDF and CDF
    for (int c = 1; c < histSize; c++)
    {
        line(pdfImage, Point(pointWidth * (c - 1), histHeight - cvRound(pdf.at<float>(c - 1))),
            Point(pointWidth * c, histHeight - cvRound(pdf.at<float>(c))),
            Scalar(255, 0, 0), 2);
        line(cdfImage, Point(pointWidth * (c - 1), histHeight - cvRound(cdf.at<float>(c - 1))),
            Point(pointWidth * c, histHeight - cvRound(cdf.at<float>(c))),
            Scalar(255, 0, 0), 2);
    }

#pragma endregion

    return std::vector<Mat> { pdf, cdf, pdfImage, cdfImage };
}

std::vector<Mat> histogramMatching_Seperate(Mat* inputImage1, Mat* inputImage2)
{
#pragma region Initialization



#pragma endregion

    return std::vector<Mat>();
}

std::vector<Mat> histogramMatching_Average(Mat* inputImage1, Mat* inputImage2)
{
    return std::vector<Mat>();
}