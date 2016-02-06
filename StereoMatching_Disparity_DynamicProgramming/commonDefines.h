#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_LEFTIMAGE_STRING "l"
#define ARGUMENT_RIGHTIMAGE_STRING "r"
#define ARGUMENT_MATCHINGCRITERITA_STRING "m"
#define ARGUMENT_BLOCKSIZE_STRING "bs"
#define ARGUMENT_MAXDISPARITY_STRING "md"

// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_LEFTIMAGE_LIST ARGUMENT_LEFTIMAGE_STRING " left imgL imageLeft"
#define ARGUMENT_RIGHTIMAGE_LIST ARGUMENT_RIGHTIMAGE_STRING " right imgR imageRight"
#define ARGUMENT_MATCHINGCRITERITA_LIST ARGUMENT_MATCHINGCRITERITA_STRING " match"
#define ARGUMENT_BLOCKSIZE_LIST ARGUMENT_BLOCKSIZE_STRING " blockS size blockSize mbs minBlockS"
#define ARGUMENT_MAXDISPARITY_LIST ARGUMENT_MAXDISPARITY_STRING " maxD"


// Name of the Windows
#define LEFTIMAGE_WINDOW "LeftImage"
#define RIGHTIMAGE_WINDOW "RightImage"
#define OUTPUTNORMAL_WINDOW "Disparity"
#define OUTPUTNORMALSWITCHED_WINDOW "DisparitySwitched"
#define OUTPUT_POINTCLOUD_WINDOW "ColordPointCloud"
#define OUTPUT_OTIMALBLOCKSIZE_WINDOW "OptimalBlockSize"

// Outputimage name and path
#define OUTPUTIMAGENORMALE_NAME "outputImage_StereoMatching_Disparity_Dynamic.jpg"
#define OUTPUTIMAGENORMAL_PATH "../Bilder/Output/" OUTPUTIMAGENORMALE_NAME

#endif // COMMONDEFINES_H#
