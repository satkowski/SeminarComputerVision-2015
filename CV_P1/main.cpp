//-img=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\00013.jpg
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Initialization

    Mat inputImage, gradientMat; 
    std::list<Point> pointList;
    int threshhold = 1;
    Vec<void*, 4> data(&threshhold, &gradientMat, &pointList, &inputImage);

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

#pragma endregion

    gradientMat = getGradientMat(&inputImage);
    pointList = getPriorityList(&gradientMat);

#pragma region Setting Window

    // Creating window for the outputimage
    namedWindow(OUTPUTIMAGE_WINDOW, 0);
    imshow(OUTPUTIMAGE_WINDOW, inputImage);

    // Creating window for the original image
    namedWindow(INPUTIMAGE_WINDOW, 0);
    imshow(INPUTIMAGE_WINDOW, inputImage);

    // Adding the maxdistance trackbar to the window
    createTrackbar("Threshhold", OUTPUTIMAGE_WINDOW, &threshhold, 50, onThreshholdTrackbar, &data);

#pragma endregion

    waitKey();
    return 0;
}

Mat getGradientMat(Mat* image)
{
#pragma region Initialization

    Mat inputImage;
    image->convertTo(inputImage, CV_64FC3);

    Mat partDerivX = Mat(image->rows, image->cols, CV_64FC3);
    Mat partDerivY = Mat(image->rows, image->cols, CV_64FC3);
    Mat deriv = Mat(image->rows, image->cols, CV_64FC3);

#pragma endregion

#pragma region Gradient in both directions

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

#pragma endregion

    // Add the two gradients together
    for (int cX = 0; cX < image->cols; cX++)
        for (int cY = 0; cY < image->rows; cY++)
            deriv.at<Vec3d>(cY, cX) = partDerivX.at<Vec3d>(cY, cX) + partDerivY.at<Vec3d>(cY, cX);

    return deriv;
}

std::list<Point> getPriorityList(Mat* gradientMat)
{
    // Sort all Points
    Vec3dPointMap map = Vec3dPointMap();
    for (int cY = 1; cY < gradientMat->rows; cY++)
        for (int cX = 1; cX < gradientMat->cols; cX++)
            map.insert(std::pair<Vec3d, Point>(gradientMat->at<Vec3d>(cY, cX), Point(cX, cY)));
    // Put only the points in the list
    std::list<Point> priorityList = std::list<Point>();
    for each (std::pair<Vec3d, Point> pair in map)
        priorityList.push_back(pair.second);

    return priorityList;
}

static void onThreshholdTrackbar(int, void* userdata)
{
#pragma region Casting of userdata

    Vec<void*, 4> data = *static_cast<Vec<void*, 4>*>(userdata);
    int* threshhold = static_cast<int*>(data.val[0]);
    Mat* gradientMat = static_cast<Mat*>(data.val[1]);
    std::list<Point> priorityList = *static_cast<std::list<Point>*>(data.val[2]);
    Mat* outputImagePtr = static_cast<Mat*>(data.val[3]);
    Mat outputImage;
    outputImagePtr->copyTo(outputImage);

#pragma endregion
    
#pragma region Initialization

    // Generate the offset list for a 4 connect
    std::list<Point> nextPixelOffset = std::list<Point>();
    nextPixelOffset.push_back(Point(0, -1));
    nextPixelOffset.push_back(Point(1, 0));
    nextPixelOffset.push_back(Point(0, 1));
    nextPixelOffset.push_back(Point(-1, 0));
    // Mat to controll if a pixel is a super pixel allready
    Mat_<bool> avaibleMat = Mat_<bool>(outputImage.rows, outputImage.cols, true);
    avaibleMat.at<bool>(*priorityList.begin()) = false;

#pragma endregion

    while (priorityList.size() > 0)
    {
#pragma region Initialization

        // List for possible pixel that are in the super pixel
        std::list<Point> superPixelPixels = std::list<Point>();
        superPixelPixels.push_back(*priorityList.begin());
        // Varaibles to compute mean color value
        Vec3i colorSum = static_cast<Vec3i>(outputImage.at<Vec3b>(*superPixelPixels.begin()));
        int pixelConuter = 1;

#pragma endregion

#pragma region Getting super pixel pixels

        std::list<Point>::iterator superPixelPixelsIter = superPixelPixels.begin();
        for (int i = 0; i < superPixelPixels.size(); i++)
        {
            // Look on all neighbours of an pixel (4 connect)
            for each (Point pointOffset in nextPixelOffset)
            {
                // Calculate 4 connect point from offset and the actual point
                Point nextPoint = *superPixelPixelsIter + pointOffset;
                // If pixel isn't in the image borders that pixel will be ignored
                if (0 > nextPoint.x || nextPoint.x >= outputImage.cols ||
                    0 > nextPoint.y || nextPoint.y >= outputImage.rows)
                    continue;
                // If the distance is less than the threshhold and the pixel is avaible
                if (avaibleMat.at<bool>(nextPoint) &&
                    lengthVec3d(gradientMat->at<Vec3d>(nextPoint) - gradientMat->at<Vec3d>(*priorityList.begin())) <= *threshhold)
                {
                    superPixelPixels.push_back(nextPoint);
                    avaibleMat.at<bool>(nextPoint) = false;
                    colorSum += static_cast<Vec3i>(outputImage.at<Vec3b>(nextPoint));
                    pixelConuter++;
                }
            }
            // Remove finished pixel from the priorityList
            priorityList.remove(*superPixelPixels.begin());
            // Increment the pointer on the list
            ++superPixelPixelsIter;
        }

#pragma endregion

#pragma region Setting mean color

        colorSum /= pixelConuter;
        Vec3b colorSumVec3b = static_cast<Vec3b>(colorSum);
        for each (Point finishedPoint in superPixelPixels)
            outputImage.at<Vec3b>(finishedPoint) = colorSumVec3b;

#pragma endregion
    }

    imshow(OUTPUTIMAGE_WINDOW, outputImage);
}
