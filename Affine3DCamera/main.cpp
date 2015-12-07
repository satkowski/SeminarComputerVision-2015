//-img=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\flagge.jpg
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Argument parsing

    // Creating a keymap for all the arguments that can passed to that programm
    const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
                          "{" ARGUMENT_INPUTIMAGE_LIST " |   | soruce image path}";

    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("AffineCamera");

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
    Mat image = imread(imagePath, CV_LOAD_IMAGE_COLOR);
    if (image.empty())
    {
        printf("Cannot read the image %s\n", imagePath);
        return -1;
    }

#pragma endregion

#pragma region Creating the data vector

    Vec3i sphereCoordinates = Vec3i(0, 0, 0);
    Vec3i affineTransValues = Vec3i(0, 0, 0);
    Point3d cameraPosition;
    Mat rotationMat = Mat_<double>(3, 3);

    Vec<void*, 4> data(&sphereCoordinates, &cameraPosition, &rotationMat, &affineTransValues);

#pragma endregion

#pragma region Setting the windows

    namedWindow(INPUTIMAGE_WINDOW, 0);
    imshow(INPUTIMAGE_WINDOW, image);

    namedWindow(AFFINECAMERA_WINDOW, 0);

#pragma endregion

    waitKey();
    return 0;
}