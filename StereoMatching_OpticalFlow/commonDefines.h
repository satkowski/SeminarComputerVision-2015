#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_LEFTIMAGE_STRING "l"
#define ARGUMENT_RIGHTIMAGE_STRING "r"
#define ARGUMENT_MATCHINGCRITERITA_STRING "m"
#define ARGUMENT_BLOCKSIZE_STRING "bs"
#define ARGUMENT_MAXFLOW_STRING "mf"

// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_LEFTIMAGE_LIST ARGUMENT_LEFTIMAGE_STRING " left imgL imageLeft"
#define ARGUMENT_RIGHTIMAGE_LIST ARGUMENT_RIGHTIMAGE_STRING " right imgR imageRight"
#define ARGUMENT_MATCHINGCRITERITA_LIST ARGUMENT_MATCHINGCRITERITA_STRING " match"
#define ARGUMENT_BLOCKSIZE_LIST ARGUMENT_BLOCKSIZE_STRING " blockS size blockSize mbs minBlockS"
#define ARGUMENT_MAXFLOW_LIST ARGUMENT_MAXFLOW_STRING " maxF"

// Name of the Windows
#define LEFTIMAGE_WINDOW "LeftImage"
#define RIGHTIMAGE_WINDOW "RightImage"
#define OUTPUTIMAGE_WINDOW "OpticalFlow"

// Outputimage name and path
#define OUTPUTIMAGE_NAME "outputImage_StereoMatching_OpticalFlow.jpg"
#define OUTPUTIMAGE_PATH "../Bilder/Output/" OUTPUTIMAGE_NAME

#define PI 3.14159265359

#endif // COMMONDEFINES_H#
