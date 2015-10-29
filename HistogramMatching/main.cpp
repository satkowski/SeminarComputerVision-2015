//-img1=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\spine.jpg -img2=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\lena_gray.jpg
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Argument parsing

    // Creating a keymap for all the arguments that can passed to that programm
    const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
                          "{" ARGUMENT_INPUTIMAGE_1_LIST " |   | first input image path}"
                          "{" ARGUMENT_INPUTIMAGE_2_LIST " |   | second input image path}"
                          "{" ARGUMENT_COLOUR_LIST " | false | should be use colour histograms}";

    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("Superpixel");

    // If help was in the list, the help list will printed
    if (parser.has(ARGUMENT_HELP_STRING))
    {
        parser.printMessage();
        return 0;
    }

    // Get if the matching should be in colour or not
    bool colourMatching = parser.has(ARGUMENT_COLOUR_STRING);

    // Creating the first image and testing if it is empty or not
    String imagePath1 = parser.get<String>(ARGUMENT_INPUTIMAGE_1_STRING);
    if (imagePath1 == "")
    {
        printf("The first image path is empty\n");
        return -1;
    }
    Mat inputImage1;
    if (colourMatching)
        inputImage1 = imread(imagePath1, CV_LOAD_IMAGE_COLOR);
    else
        inputImage1 = imread(imagePath1, CV_LOAD_IMAGE_GRAYSCALE);
    if (inputImage1.empty())
    {
        printf("Cannot read the image %s\n", imagePath1);
        return -1;
    }

    // Creating the second image and testing if it is empty or not
    String imagePath2 = parser.get<String>(ARGUMENT_INPUTIMAGE_2_STRING);
    if (imagePath2 == "")
    {
        printf("The second image path is empty\n");
        return -1;
    }
    Mat inputImage2;
    if (colourMatching)
        inputImage2 = imread(imagePath2, CV_LOAD_IMAGE_COLOR);
    else
        inputImage2 = imread(imagePath2, CV_LOAD_IMAGE_GRAYSCALE);
    if (inputImage2.empty())
    {
        printf("Cannot read the image %s\n", imagePath2);
        return -1;
    }

#pragma endregion

#pragma region Decide the method

    std::vector<Mat> outputImages;
    if (!colourMatching)
        outputImages = histogramMatching_OneChannel(&inputImage1, &inputImage2);
    else
        outputImages = histogramMatching_ThreeChannel(&inputImage1, &inputImage2);

#pragma endregion

#pragma region Setting the windows
    
    // Creating window for the input images
    namedWindow(INPUTIMAGE_1_WINDOW, 0);
    imshow(INPUTIMAGE_1_WINDOW, inputImage1);
    namedWindow(INPUTIMAGE_2_WINDOW, 0);
    imshow(INPUTIMAGE_2_WINDOW, inputImage2);

    // Creating window for the output images
    namedWindow(OUTPUTIMAGE_CDF_WINDOW, 0);
    imshow(OUTPUTIMAGE_CDF_WINDOW, outputImages.at(3));
    namedWindow(OUTPUT_HISTOGRAM_CDF_1_WINDOWS, 0);
    imshow(OUTPUT_HISTOGRAM_CDF_1_WINDOWS, outputImages.at(0));
    namedWindow(OUTPUT_HISTOGRAM_CDF_2_WINDOWS, 0);
    imshow(OUTPUT_HISTOGRAM_CDF_2_WINDOWS, outputImages.at(1));

    // Save all images
    imwrite(OUTPUTIMAGE_CDF_PATH, outputImages.at(3));
    imwrite(OUTPUT_HISTOGRAM_CDF_1_PATH, outputImages.at(0));
    imwrite(OUTPUT_HISTOGRAM_CDF_2_PATH, outputImages.at(1));

#pragma endregion

    waitKey();
    return 0;
}