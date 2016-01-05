#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_LEFTIMAGE_STRING "l"
#define ARGUMENT_RIGHTIMAGE_STRING "r"
#define ARGUMENT_MATCHINGCRITERITA_STRING "m"
#define ARGUMENT_BLOCKSIZE_STRING "bs"
#define ARGUMENT_POSTPROCESSING_STRING "pp"
#define ARGUMENT_MAXDISPARITY_STRING "md"
#define ARGUMENT_COLOREDPOINTCLOUD_STRING "cpc"
#define ARGUMENT_OPTMIMALBLOCKSIZE_STRING "obs"

// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_LEFTIMAGE_LIST ARGUMENT_LEFTIMAGE_STRING " left imgL imageLeft"
#define ARGUMENT_RIGHTIMAGE_LIST ARGUMENT_RIGHTIMAGE_STRING " right imgR imageRight"
#define ARGUMENT_MATCHINGCRITERITA_LIST ARGUMENT_MATCHINGCRITERITA_STRING " match"
#define ARGUMENT_BLOCKSIZE_LIST ARGUMENT_BLOCKSIZE_STRING " blockS size blockSize mbs minBlockS"
#define ARGUMENT_POSTPROCESSING_LIST ARGUMENT_POSTPROCESSING_STRING " postP"
#define ARGUMENT_MAXDISPARITY_LIST ARGUMENT_MAXDISPARITY_STRING " maxD"
#define ARGUMENT_COLOREDPOINTCLOUD_LIST ARGUMENT_COLOREDPOINTCLOUD_STRING " coloredPointCloud"
#define ARGUMENT_OPTMIMALBLOCKSIZE_LIST ARGUMENT_OPTMIMALBLOCKSIZE_STRING " optimalBlockSize"

// Name of the Windows
#define LEFTIMAGE_WINDOW "LeftImage"
#define RIGHTIMAGE_WINDOW "RightImage"
#define OUTPUTNORMAL_WINDOW "Disparity"
#define OUTPUTNORMALSWITCHED_WINDOW "DisparitySwitched"
#define OUTPUT_POINTCLOUD_WINDOW "ColordPointCloud"

// Outputimage name and path
#define OUTPUTIMAGENORMALE_NAME "outputImage_StereoMatching_Disparity.jpg"
#define OUTPUTIMAGENORMAL_PATH "../Bilder/Output/" OUTPUTIMAGENORMALE_NAME
#define OUTPUTIMAGESWITCHED_NAME "outputImage_StereoMatching_DisparitySwitched.jpg"
#define OUTPUTIMAGESWITCHED_PATH "../Bilder/Output/" OUTPUTIMAGESWITCHED_NAME
#define OUTPUTIMAGE_POINTCLOUD_NAME "outputImage_StereoMatching_PointCloud.jpg"
#define OUTPUTIMAGE_POINTCLOUD_PATH "../Bilder/Output/" OUTPUTIMAGE_POINTCLOUD_NAME

// Postprocessing parameters
#define MEDIANSIZE 5

// Colourd point cloud parameters
// That parameters are for the 2 images in the "Bilder" folder (left2.png and right2.png)
#define DISTANCE_BETWEEN_IMAGES 8
#define DEPTH_OF_OBJECT 280
#define OBJECT_POSITION_X 229
#define OBJECT_POSITION_Y 126

// Optimal block size calculation
#define TIMES_BLOCKRADIUS_CHANGED 4

#endif // COMMONDEFINES_H#
