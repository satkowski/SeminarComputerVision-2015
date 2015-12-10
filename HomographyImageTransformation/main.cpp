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

#pragma region Creating the data vector

    std::vector<Point2f> sourcePointVector, destinationPointVector;
    sourcePointVector.push_back(Point2f(0, 0));
    sourcePointVector.push_back(Point2f(0, sourceImage.rows - 1));
    sourcePointVector.push_back(Point2f(sourceImage.cols - 1, sourceImage.rows - 1));
    sourcePointVector.push_back(Point2f(sourceImage.cols - 1, 0));

    Vec<void*, 4> data = { &sourceImage, &destinationImage, &sourcePointVector, &destinationPointVector };

#pragma endregion

#pragma region Setting the windows

    namedWindow(OUTPUTIMAGE_WINDOW, 0);

    // Creating windows for the input images
    namedWindow(SOURCEIMAGE_WINDOW, 0);
    imshow(SOURCEIMAGE_WINDOW, sourceImage);
    namedWindow(DESTINATIONIMAGE_WINDOW, 0);
    imshow(DESTINATIONIMAGE_WINDOW, destinationImage);
    setMouseCallback(DESTINATIONIMAGE_WINDOW, mouseListener, &data);

#pragma endregion

    waitKey();
    return 0;
}

void mouseListener(int event, int x, int y, int, void* userdata)
{
#pragma region Casting of the arguments 1

    Vec<void*, 4>* data = static_cast<Vec<void*, 4>*>(userdata);
    Mat destinationImage = *static_cast<Mat*>(data->val[1]);
    std::vector<Point2f>* destinationPointVector = static_cast<std::vector<Point2f>*>(data->val[3]);

#pragma endregion

#pragma region Input handling
    
    // On left doubleclick the points will be selected
    if (event == EVENT_LBUTTONDOWN)
    {
        destinationPointVector->push_back(Point2f(x, y));

        // Draw the point in the destination image and show it
        circle(destinationImage, Point(x, y), 7, Scalar(0, 0, 255), CV_FILLED);
        imshow(DESTINATIONIMAGE_WINDOW, destinationImage);
    }

#pragma endregion

#pragma region Transform the image
    
    // If there are 4 point selected transform the image
    if (destinationPointVector->size() >= 4)
    {
#pragma region Casting of the arguments

        Mat* sourceImage = static_cast<Mat*>(data->val[0]);
        std::vector<Point2f>* sorucePointVector = static_cast<std::vector<Point2f>*>(data->val[2]);

#pragma endregion

        //Deactivate the mouselistener
        setMouseCallback(DESTINATIONIMAGE_WINDOW, NULL);

        // Create homography and transform the source image
        Mat sourceWarped;
        Mat homography = findHomography(*sorucePointVector, *destinationPointVector);
        warpPerspective(*sourceImage, sourceWarped, homography, destinationImage.size());

        // Creates an aquivalent gray image of the warped image, makes it binary and invert
        Mat gray, grayInv;
        cvtColor(sourceWarped, gray, CV_BGR2GRAY);
        threshold(gray, gray, 0, 256, CV_THRESH_BINARY);
        bitwise_not(gray, grayInv);

        // Copy only those pixel that got an 1 in the mask
        Mat destinationFinal, sourceFinal;
        sourceWarped.copyTo(sourceFinal, gray);
        destinationImage.copyTo(destinationFinal, grayInv);

        // Combine the two images
        Mat finalImage = destinationFinal + sourceFinal;
        imshow(OUTPUTIMAGE_WINDOW, finalImage);
    }

#pragma endregion
}

