#include "main.h"

using namespace cv;

int main(int argc, const char** argv)
{
#pragma region Argument parsing

	// Creating a keymap for all the arguments that can passed to that programm
	const String keyMap = "{" ARGUMENT_HELP_LIST " |   | show this message}"
					      "{" ARGUMENT_INPUTIMAGE_LIST " |   | input image path}";

    // Reading the calling arguments
    CommandLineParser parser(argc, argv, keyMap);
    parser.about("FaceDetection-HOG-SVM");

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

#pragma endregion
}