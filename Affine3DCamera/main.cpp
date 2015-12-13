//-img=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\fruits.jpg
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

#pragma region Initialize data
    
    Vec3i sphereCoordinates = Vec3i(150, 0, 0);
    Vec3i affineTransValues = Vec3i(0, 0, 1);
    Point3d cameraPosition = Point3d(0);
    Mat rotationMatCamera, rotationMatAffine, intrinsicCameraMat;
    std::vector<Point2f> sourceImagePoints, sourceImagePointsShift, cameraImagePoints;

    Vec<void*, 10> data(&sphereCoordinates, &affineTransValues, &cameraPosition, 
                        &rotationMatCamera, &rotationMatAffine,
                        &sourceImagePoints, &sourceImagePointsShift, &cameraImagePoints,
                        &intrinsicCameraMat,
                        &image);

    fillingUserdata(&data);

#pragma endregion

    calcRotationMatAffine(&data);
    onTrackbarCam(0, &data);

#pragma region Setting the windows

    namedWindow(INPUTIMAGE_WINDOW, 0);
    imshow(INPUTIMAGE_WINDOW, image);
    namedWindow(CAMERA_WINDOW, 0);

    //Adding the trackbars for the spherical coordinates
    createTrackbar("radius", CAMERA_WINDOW, &(sphereCoordinates.val[0]), ALPHA * 15, onTrackbarCam, &data);
    createTrackbar("theta ", CAMERA_WINDOW, &(sphereCoordinates.val[1]), 89, onTrackbarRotMat, &data);
    createTrackbar("rho   ", CAMERA_WINDOW, &(sphereCoordinates.val[2]), 360, onTrackbarRotMat, &data);

    namedWindow(AFFINEIMAGE_WINDOW, 0);
    //Adding the trackbars for the affine transformation
    createTrackbar("alpha", AFFINEIMAGE_WINDOW, &(affineTransValues.val[0]), 360, onTrackbarAff, &data);
    createTrackbar("beta ", AFFINEIMAGE_WINDOW, &(affineTransValues.val[1]), 360, onTrackbarAff, &data);
    createTrackbar("lamda", AFFINEIMAGE_WINDOW, &(affineTransValues.val[2]), 15, onTrackbarAff, &data);

#pragma endregion

    waitKey();
    return 0;
}

static void onTrackbarCam(int, void* userdata)
{
    Mat cameraImage = calcCameraImage(userdata);
    Mat affineImage = calcAffineTransformation(userdata);

    imshow(AFFINEIMAGE_WINDOW, affineImage);
    imshow(CAMERA_WINDOW, cameraImage);
}

static void onTrackbarAff(int, void* userdata)
{
    calcRotationMatAffine(userdata);
    Mat affineImage = calcAffineTransformation(userdata);

    imshow(AFFINEIMAGE_WINDOW, affineImage);
}

static void onTrackbarRotMat(int, void* userdata)
{
    calcRotationMatCamera(userdata);

    onTrackbarCam(0, userdata);
}