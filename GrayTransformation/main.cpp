#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{

#pragma region Initialization

    Mat inputImage;

#pragma endregion

#pragma region Argument parsing

    // Creating a keymap for all the arguments that can passed to that programm
    const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
                          "{" ARGUMENT_INPUTIMAGE_LIST " |   | input image path}"
                          "{" ARGUMENT_TRANSFORMATION_LIST " | 0 | transformationType:\n 0 - log\n 1 - powe-law\n 2 - another}";
    
    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("Superpixel");

    // If help was in the list, the help list will printed
    if (parser.has(ARGUMENT_HELP_STRING))
    {
        parser.printMessage();
        return 0;
    }

    // Try to parse the path in an image
    String imagePath = parser.get<String>(ARGUMENT_INPUTIMAGE_STRING);
    if (imagePath == "")
    {
        printf("The Path is empty\n");
        return -1;
    }

    // Creating the image and testing if it is empty or not
    inputImage = imread(imagePath, CV_LOAD_IMAGE_COLOR);
    if (inputImage.empty())
    {
        printf("Cannot read the image %s\n", imagePath.c_str());
        return -1;
    }

    // Get what function shoudl be used
    int transformationType = parser.get<int>(ARGUMENT_TRANSFORMATION_STRING);
    if (transformationType < 0 || transformationType > 2)
    {
        printf("No valid transformation type\n");
        return -1;
    }

#pragma endregion

}