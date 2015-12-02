//-src=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\flagge.jpg -dst=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\schwimmbahn.jpg
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Argument parsing

    // Creating a keymap for all the arguments that can passed to that programm
    const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
                          "{" ARGUMENT_SOURCEIMAGE_LIST " |   | soruce image path}"
                          "{" ARGUMENT_DESTINATIONIMAGE_LIST " |   | destination image path}";

    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("Histogram Matching");
    
    // If help was in the list, the help list will printed
    if (parser.has(ARGUMENT_HELP_STRING))
    {
        parser.printMessage();
        return 0;
    }

    // Creating the first image and testing if it is empty or not
    String sourceImagePath = parser.get<String>(ARGUMENT_SOURCEIMAGE_STRING);
    if (sourceImagePath == "")
    {
        printf("The first image path is empty\n");
        return -1;
    }
    Mat sourceImage = imread(sourceImagePath, CV_LOAD_IMAGE_COLOR);
    if (sourceImage.empty())
    {
        printf("Cannot read the image %s\n", sourceImagePath);
        return -1;
    }

    // Creating the second image and testing if it is empty or not
    String destinationImagePath = parser.get<String>(ARGUMENT_DESTINATIONIMAGE_STRING);
    if (destinationImagePath == "")
    {
        printf("The second image path is empty\n");
        return -1;
    }
    Mat destinationImage = imread(destinationImagePath, CV_LOAD_IMAGE_COLOR);
    if (destinationImage.empty())
    {
        printf("Cannot read the image %s\n", destinationImagePath);
        return -1;
    }

#pragma endregion

#pragma region Setting the windows

    // Creating windows for the input images
    namedWindow(SOURCEIMAGE_WINDOW, 0);
    imshow(SOURCEIMAGE_WINDOW, sourceImage);
    namedWindow(DESTINATIONIMAGE_WINDOW, 0);
    imshow(DESTINATIONIMAGE_WINDOW, destinationImage);

#pragma endregion

    waitKey();
    return 0;
}