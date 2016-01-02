#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_LEFTIMAGE_STRING "l"
#define ARGUMENT_RIGHTIMAGE_STRING "r"
#define ARGUMENT_MATCHINGCRITERITA_STRING "m"
#define ARGUMENT_BLOCKSIZE_STRING "bs"
#define ARGUMENT_POSTPROCESSING_STRING "pp"

// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_LEFTIMAGE_LIST ARGUMENT_LEFTIMAGE_STRING " left imgL imageLeft"
#define ARGUMENT_RIGHTIMAGE_LIST ARGUMENT_RIGHTIMAGE_STRING " right imgR imageRight"
#define ARGUMENT_MATCHINGCRITERITA_LIST ARGUMENT_MATCHINGCRITERITA_STRING " match"
#define ARGUMENT_BLOCKSIZE_LIST ARGUMENT_BLOCKSIZE_STRING " blockS size blockSize"
#define ARGUMENT_POSTPROCESSING_LIST ARGUMENT_POSTPROCESSING_STRING " postP"

// Name of the Windows
#define LEFTIMAGE_WINDOW "LeftImage"
#define RIGHTIMAGE_WINDOW "RightImage"
#define OUTPUTNORMAL_WINDOW "Disparity"
#define OUTPUTNORMALSWITCHED_WINDOW "DisparitySwitched"

// Outputimage name and path
#define OUTPUTIMAGENORMALE_NAME "outputImage_StereoMatching_Disparity.jpg"
#define OUTPUTIMAGENORMAL_PATH "../Bilder/Output/" OUTPUTIMAGENORMALE_NAME
#define OUTPUTIMAGESWITCHED_NAME "outputImage_StereoMatching_Disparity.jpg"
#define OUTPUTIMAGESWITCHED_PATH "../Bilder/Output/" OUTPUTIMAGESWITCHED_NAME

// Postprocessing variables
#define MEDIANSIZE 4

#endif // COMMONDEFINES_H#
