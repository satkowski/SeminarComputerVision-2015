//-l=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\left2.png -r=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\right2.png -m=0 -bs=2
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Argument parsing

    // Creating a keymap for all the arguments that can passed to that programm
    const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
                          "{" ARGUMENT_LEFTIMAGE_LIST " |   | left soruce image path}"
                          "{" ARGUMENT_RIGHTIMAGE_LIST " |   | right soruce image path}"
                          "{" ARGUMENT_MATCHINGCRITERITA_LIST " | 0 | matching criteria:\n 0 - SSD\n 1 - ASD\n 2 - Cross Correlation}"
                          "{" ARGUMENT_BLOCKSIZE_LIST " | 2 | radius around an pixel for the patch}"
                          "{" ARGUMENT_MAXDISPARITY_LIST " | 8 | maximum disparity of a pixel}"
                          "{" ARGUMENT_POSTPROCESSING_LIST " |   | should be post processing (median, left-right-consitency) activated}";

    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("StereoMatching-DisparityCalculation");

    // If help was in the list, the help list will printed
    if (parser.has(ARGUMENT_HELP_STRING))
    {
        parser.printMessage();
        return 0;
    }

    // Creating the images and testing if it is empty or not
    String leftImagePath = parser.get<String>(ARGUMENT_LEFTIMAGE_STRING);
    if (leftImagePath == "")
    {
        printf("The first image path is empty\n");
        return -1;
    }
    Mat leftImage = imread(leftImagePath, CV_LOAD_IMAGE_COLOR);
    if (leftImage.empty())
    {
        printf("Cannot read the image %s\n", leftImagePath);
        return -1;
    }
    String rightImagePath = parser.get<String>(ARGUMENT_RIGHTIMAGE_STRING);
    if (rightImagePath == "")
    {
        printf("The first image path is empty\n");
        return -1;
    }
    Mat rightImage = imread(rightImagePath, CV_LOAD_IMAGE_COLOR);
    if (rightImage.empty())
    {
        printf("Cannot read the image %s\n", rightImagePath);
        return -1;
    }
    
    int matchingCriteria = parser.get<int>(ARGUMENT_MATCHINGCRITERITA_STRING);
    if (0 > matchingCriteria || matchingCriteria > 2)
    {
        printf("No matchingcriteria with the number %d\n", matchingCriteria);
        return -1;
    }
    int blockRadius = parser.get<int>(ARGUMENT_BLOCKSIZE_STRING);
    if (blockRadius <= 0)
    {
        printf("The block radius cannot be negativ. Yours is %d\n", blockRadius);
        return -1;
    }
    int maxDisparity = parser.get<int>(ARGUMENT_MAXDISPARITY_STRING);
    if (maxDisparity <= 0)
    {
        printf("The max disparity cannot be negativ. Yours is %d\n", blockRadius);
        return -1;        
    }
    bool postProc = parser.has(ARGUMENT_POSTPROCESSING_STRING);

#pragma endregion

    Vec<void*, 5> data(&leftImage, &rightImage, &blockRadius, &matchingCriteria, &maxDisparity);
    Mat outputImage = calcDisparity(&data, true);

#pragma region Post processing

    Mat outputImageSwitched;
    if (postProc)
    {
        data.val[0] = &rightImage;
        data.val[1] = &leftImage;

        outputImageSwitched = calcDisparity(&data, false);

        postProccesing(&outputImage, &outputImageSwitched);
    }
    else
        outputImage.convertTo(outputImage, CV_8U);

#pragma endregion

#pragma region Setting the windows

    namedWindow(LEFTIMAGE_WINDOW, 0);
    imshow(LEFTIMAGE_WINDOW, leftImage);
    namedWindow(RIGHTIMAGE_WINDOW, 0);
    imshow(RIGHTIMAGE_WINDOW, rightImage);
    namedWindow(OUTPUTNORMAL_WINDOW, 0);
    imshow(OUTPUTNORMAL_WINDOW, outputImage);
    if (postProc)
    {
        namedWindow(OUTPUTNORMALSWITCHED_WINDOW, 0);
        imshow(OUTPUTNORMALSWITCHED_WINDOW, outputImageSwitched);
        imwrite(OUTPUTIMAGESWITCHED_PATH, outputImageSwitched);
    }

#pragma endregion

    imwrite(OUTPUTIMAGENORMAL_PATH, outputImage);

    waitKey();
    return 0;
}
