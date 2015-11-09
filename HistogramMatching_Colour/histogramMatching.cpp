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

std::vector<Mat> histogramMatching(Mat* inputImage1, Mat* inputImage2, bool seperate)
{
#pragma region Initialization

    Mat imageSplit1[3], imageSplit2[3];
    std::vector<Mat> imageMats1[3], imageMats2[3];
    Mat cdf1[3], cdf2[4];
    Mat lutChannel[3];
    Mat cdfOutput = Mat(inputImage1->rows, inputImage1->cols, CV_8UC3);

#pragma endregion

#pragma region Get all data

    split(*inputImage1, imageSplit1);
    split(*inputImage2, imageSplit2);

    for (int c = 0; c < 3; c++)
    {
        imageMats1[c] = calcCDFandPDF(&imageSplit1[c]);
        imageMats2[c] = calcCDFandPDF(&imageSplit2[c]);
        cdf1[c] = imageMats1[c].at(1);
        cdf2[c] = imageMats2[c].at(1);
        lutChannel[c] = Mat(cdf1[c].rows, 1, CV_8U);
    }

    cdf2[3] = cdf2[0] + cdf2[1] + cdf2[2];
    cdf2[3] /= 3;
    
#pragma endregion

#pragma region Histogram matching

    int oldC2[3] = { 0, 0, 0 };
    for (int c1 = 0; c1 < cdf1[0].rows; c1++)
        for (int channel = 0; channel < 3; channel++)
            for (int c2 = oldC2[channel]; c2 < cdf2[channel].rows; c2++)
            {
                int cdf2Channel = seperate ? channel : 3;
                if (cdf1[channel].at<float>(c1) > cdf2[cdf2Channel].at<float>(c2) && (c2 + 1) != cdf2[cdf2Channel].rows)
                    continue;
                lutChannel[channel].at<uchar>(c1) = static_cast<uchar>(c2);
                // Save old c2 because the value before were less
                oldC2[channel] = c2;
                break;
            }

#pragma endregion
    
#pragma region Calculate the output image

    for (int cY = 0; cY < cdfOutput.rows; cY++)
        for (int cX = 0; cX < cdfOutput.cols; cX++)
        {
            Vec3b pixel = inputImage1->at<Vec3b>(cY, cX);
            cdfOutput.at<Vec3b>(cY, cX) = Vec3b{ lutChannel[0].at<uchar>(pixel.val[0]),
                                                 lutChannel[1].at<uchar>(pixel.val[1]),
                                                 lutChannel[2].at<uchar>(pixel.val[2]) };
        }

#pragma endregion

    return std::vector<Mat> { imageMats1[0].at(3), imageMats1[1].at(3), imageMats1[2].at(3), 
                              imageMats1[0].at(2), imageMats1[1].at(2), imageMats1[2].at(2), 
                              cdfOutput };
}