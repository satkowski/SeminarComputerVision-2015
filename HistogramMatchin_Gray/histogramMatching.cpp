#include "histogramMatching.h"

using namespace cv;


std::vector<Mat> calcCDFandPDF(Mat* input)
{
#pragma region Initialization

    Mat pdf, cdf;
    float range[2] { 0, 255 };
    const float* ranges[1] { range };
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
                       Point(pointWidth * c,       histHeight - cvRound(cdf.at<float>(c))),
             Scalar(255, 0, 0), 2);
    }

#pragma endregion

    return std::vector<Mat> { pdf, cdf, pdfImage, cdfImage };
}

std::vector<Mat> histogramMatching_OneChannel(Mat* inputImage1, Mat* inputImage2)
{
#pragma region Initialization

    // Get the Mat that are needed to calculate the histogram matching
    std::vector<Mat> imageMats1 = calcCDFandPDF(inputImage1);
    std::vector<Mat> imageMats2 = calcCDFandPDF(inputImage2);
    Mat cdf1 = imageMats1.at(1);
    Mat cdf2 = imageMats2.at(1);
    Mat lut = Mat(cdf1.rows, 1, CV_8U);
    
    Mat firstImage;
    inputImage1->copyTo(firstImage);
    Mat pdfOutput = Mat(inputImage1->rows, inputImage1->cols, CV_8U);
    Mat cdfOutput = Mat(inputImage1->rows, inputImage1->cols, CV_8U);

#pragma endregion

#pragma region Histogram matching

    // Go over all values and compare them
    int oldC2 = 0;
    for (int c1 = 0; c1 < cdf1.rows; c1++)
        for (int c2 = oldC2; c2 < cdf2.rows; c2++)
        {
            if (cdf1.at<float>(c1) > cdf2.at<float>(c2) && (c2 + 1) != cdf2.rows)
                continue;
            lut.at<uchar>(c1) = static_cast<uchar>(c2);
            // Save old c2 because the values before were less
            oldC2 = c2;
            break;
        }

#pragma endregion

#pragma region Calculate the output images

    equalizeHist(firstImage, pdfOutput);

    // Calculate the cdf image
    for (int cY = 0; cY < cdfOutput.rows; cY++)
        for (int cX = 0; cX < cdfOutput.cols; cX++)
            cdfOutput.at<uchar>(cY, cX) = lut.at<uchar>(inputImage1->at<uchar>(cY, cX));

#pragma endregion

    return std::vector<Mat> { imageMats1.at(3), imageMats2.at(3), pdfOutput, cdfOutput};
}