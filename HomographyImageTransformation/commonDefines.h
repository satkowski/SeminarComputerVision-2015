#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_SOURCEIMAGE_STRING "src"
#define ARGUMENT_DESTINATIONIMAGE_STRING "dst"
// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_SOURCEIMAGE_LIST ARGUMENT_SOURCEIMAGE_STRING " soruce img1 input1"
#define ARGUMENT_DESTINATIONIMAGE_LIST ARGUMENT_DESTINATIONIMAGE_STRING " destination img2 input2"

// Name of the Windows
#define SOURCEIMAGE_WINDOW "SourceImage"
#define DESTINATIONIMAGE_WINDOW "DestinationImage"
#define OUTPUTIMAGE_WINDOW "HomographyImage"

// Outputimage name and path
#define OUTPUTIMAGE_NAME "outputImage_Homography.jpg"
#define OUTPUTIMAGE_PATH "../Bilder/Output/" OUTPUTIMAGE_NAME

#endif // COMMONDEFINES_H#
