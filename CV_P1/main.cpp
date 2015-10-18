//-img=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\00013.jpg
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Initialization

    Mat inputImage, outputImage; 
    PointVec3fQueue queue;
    int threshhold = 5;
    Vec<void*, 3> data(&threshhold, &queue, &outputImage);

#pragma endregion

#pragma region Argument parsing

	// Creating a keymap for all the arguments that can passed to that programm
	const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
					      "{" ARGUMENT_INPUTIMAGE_LIST " |   | input image path}";

    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("Superpixel");

    if (parser.has(ARGUMENT_HELP_STRING))
    {
        parser.printMessage();
        return 0;
    }

    String imagePath = parser.get<String>(ARGUMENT_INPUTIMAGE_STRING);
    if (imagePath == "")
    {
        printf("The Path is empty\n");
        return -1;
    }

    //Creating the image and testing if it is empty or not
    inputImage = imread(imagePath, CV_LOAD_IMAGE_COLOR);
    if (inputImage.empty())
    {
        printf("Cannot read the image %s\n", imagePath.c_str());
        return -1;
    }

    inputImage.copyTo(outputImage);

#pragma endregion

    queue = getPriorityQueue(&inputImage);
    onThreshholdTrackbar(0, &data);

#pragma region Setting Window

    //Creating window for the outputimage
    namedWindow(OUTPUTIMAGE_WINDOW, 0);
    imshow(OUTPUTIMAGE_WINDOW, outputImage);

    //Creating window for the original image
    namedWindow(INPUTIMAGE_WINDOW, 0);
    imshow(INPUTIMAGE_WINDOW, inputImage);

    //Adding the maxdistance trackbar to the window
    createTrackbar("Threshhold", OUTPUTIMAGE_WINDOW, &threshhold, 42, onThreshholdTrackbar, &data);

#pragma endregion

    waitKey();
    return 0;
}

PointVec3fQueue getPriorityQueue(Mat* image)
{
    Mat inputImage;
    image->convertTo(inputImage, CV_64FC3);

    Mat partDerivX = Mat(image->rows, image->cols, CV_64FC3);
    Mat partDerivY = Mat(image->rows, image->cols, CV_64FC3);
    PointVec3fQueue queue = PointVec3fQueue();

    //Calculate gradient in x direction
    for (int cY = 0; cY < image->rows; cY++)
        for (int cX = 1; cX < image->cols - 1; cX++)
        {
            Vec3d gradient = Vec3d();
            Vec3d pixelPre = inputImage.at<Vec3d>(cY, cX - 1);
            Vec3d pixelNext = inputImage.at<Vec3d>(cY, cX + 1);
            //( I(x + 1, y) - I(x - 1, y) ) / 2
            for (int i = 0; i < 3; i++)
                gradient[i] = (pixelNext.val[i] - pixelPre.val[i]) / 2;
            partDerivX.at<Vec3d>(cY, cX) = gradient;
        }

    //Calculate gradient in y direction
    for (int cX = 0; cX < image->cols; cX++)
        for (int cY = 1; cY < image->rows - 1; cY++)
        {
            Vec3d gradient = Vec3d();
            Vec3d pixelPre = inputImage.at<Vec3d>(cY - 1, cX);
            Vec3d pixelNext = inputImage.at<Vec3d>(cY + 1, cX);
            //( I(x, y + 1) - I(x, y - 1) ) / 2
            for (int i = 0; i < 3; i++)
                gradient[i] = (pixelNext.val[i] - pixelPre.val[i]) / 2;
            partDerivY.at<Vec3d>(cY, cX) = gradient;
        }

    //Add the two gradients together
    for (int cX = 0; cX < image->cols; cX++)
        for (int cY = 0; cY < image->rows; cY++)
            queue.insert(std::pair<Point, Vec3d>(Point(cX, cY), partDerivX.at<Vec3d>(cY, cX) + partDerivY.at<Vec3d>(cY, cX)));

    return queue;
}

static void onThreshholdTrackbar(int, void* userdata)
{
#pragma region Casting of userdata

    Vec<void*, 3> data = static_cast<Vec<void*, 3>*>(userdata);
    int* threshhold = static_cast<int*>(data.val[0]);
    PointVec3fQueue* queue = static_cast<PointVec3fQueue*>(data.val[1]);
    Mat* outputImage = static_cast<Mat*>(data.val[2]);

#pragma endregion


}