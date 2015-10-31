//-img=D:\Dokumente\Workspaces\C++_VS\SeminarComputerVision\Bilder\spine.jpg -type=0
#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Argument parsing

    // Creating a keymap for all the arguments that can passed to that programm
    const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
                          "{" ARGUMENT_INPUTIMAGE_LIST " |   | input image path}"
                          "{" ARGUMENT_TRANSFORMATION_LIST " | 0 | transformationType:\n 0 - log\n 1 - powe-law\n 2 - another}";
    
    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("Grey Transformation");

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
    Mat inputImage = imread(imagePath, CV_LOAD_IMAGE_COLOR);
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

#pragma region Initialization

    int sliderParameter = 1;
    int sliderMaxValue = 0;
    String sliderName = "";
    switch (transformationType)
    {
    case 0:
        sliderName = SLIDER_ALPHA_NAME;
        sliderParameter /= SLIDER_ALPHA_COEFFICENT;
        sliderMaxValue = SLIDER_ALPHA_MAX_VALUE;
        break;
    case 1:
        sliderName = SLIDER_GAMMA_NAME;
        sliderParameter /= SLIDER_GAMMA_COEFFICENT;
        sliderMaxValue = SLIDER_GAMMA_MAX_VALUE;
        break;
    case 2:
        sliderName = SLIDER_OWN_NAME;
        sliderMaxValue = SLIDER_OWNTRANSFORMATION_MAX_VALUE;
        break;        
    }
    Vec<void*, 2> data(&transformationType, &inputImage);

#pragma endregion

#pragma region Setting the different windows
    
    // Creating window for the outputimage
    namedWindow(OUTPUTIMAGE_WINDOW, 0);
    imshow(OUTPUTIMAGE_WINDOW, inputImage);

    // Creating window for the original image
    namedWindow(INPUTIMAGE_WINDOW, 0);
    imshow(INPUTIMAGE_WINDOW, inputImage);

    createTrackbar(sliderName, OUTPUTIMAGE_WINDOW, &sliderParameter, sliderMaxValue, onTrackbarChange, &data);

#pragma endregion

    waitKey();
    return 0;
}

static void onTrackbarChange(int sliderValue, void* userdata)
{
#pragma region Casting of userdata and Initialization

    // Get the date vector from the parameters and cast all parameters back
    Vec<void*, 2> data = *static_cast<Vec<void*, 2>*>(userdata);
    int* transformationType = static_cast<int*>(data.val[0]);
    Mat input, output;
    cvtColor(*static_cast<Mat*>(data.val[1]), input, CV_BGR2GRAY);
    input.convertTo(input, CV_64F);

#pragma endregion

    // Decide which transformation to use
    switch (*transformationType)
    {
    case 0:
        output = logTransformation(sliderValue, &input);      break;
    case 1:
        output = powerLawTransformation(sliderValue, &input); break;
    case 2:
        output = ownTransformation(sliderValue, &input);      break;
    }

    imshow(OUTPUTIMAGE_WINDOW, output);
    imwrite(OUTPUTIMAGE_PATH, output);
}