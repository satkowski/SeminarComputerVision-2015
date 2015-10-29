#ifndef HISTOGRAMMATCHING_H
#define HISTOGRAMMATCHING_H

#include "opencv2/imgproc/imgproc.hpp"

// Calculate the PDF and CDF of an given image
std::vector<cv::Mat> calcCDFandPDF(cv::Mat* input);
std::vector<cv::Mat> histogramMatching_OneChannel(cv::Mat* inputImage1, cv::Mat* inputImage2);
std::vector<cv::Mat> histogramMatching_ThreeChannel(cv::Mat* inputImage1, cv::Mat* inputImage2);

#endif // HISTOGRAMMATCHING_H