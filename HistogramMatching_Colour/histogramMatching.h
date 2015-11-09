#ifndef HISTOGRAMMATCHING_H
#define HISTOGRAMMATCHING_H

#include "opencv2/imgproc/imgproc.hpp"

// Calculate the PDF and CDF of an given image
std::vector<cv::Mat> calcCDFandPDF(cv::Mat* input);
std::vector<cv::Mat> histogramMatching(cv::Mat* inputImage1, cv::Mat* inputImage2, bool seperate);
std::vector<cv::Mat> histogramMatching_Average(cv::Mat* inputImage1, cv::Mat* inputImage2);

#endif // HISTOGRAMMATCHING_H