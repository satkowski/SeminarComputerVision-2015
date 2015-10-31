//-img=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\lena_gray.jpg -filter=0
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Argument parsing

    // Creating a keymap for all the arguments that can passed to that programm
    const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
                          "{" ARGUMENT_INPUTIMAGE_LIST " |   | first input image path}"
                          "{" ARGUMENT_FILTERSELECTION_LIST " | 0 | second input image path}";

    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("Filter");

    // If help was in the list, the help list will printed
    if (parser.has(ARGUMENT_HELP_STRING))
    {
        parser.printMessage();
        return 0;
    }

    // Creating the first image and testing if it is empty or not
    String imagePath = parser.get<String>(ARGUMENT_INPUTIMAGE_STRING);
    if (imagePath == "")
    {
        printf("The first image path is empty\n");
        return -1;
    }
    Mat inputImage = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
    if (inputImage.empty())
    {
        printf("Cannot read the image %s\n", imagePath);
        return -1;
    }

    // Which filter should be used
    int filter = parser.get<int>(ARGUMENT_FILTERSELECTION_STRING);

#pragma endregion

    waitKey();
    return 0;
}