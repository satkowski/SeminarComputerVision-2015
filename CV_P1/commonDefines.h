#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_INPUTIMAGE_STRING "img"
// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_INPUTIMAGE_LIST ARGUMENT_INPUTIMAGE_STRING " input"

// Name of the Windows
#define INPUTIMAGE_WINDOW "OriginalImage"
#define OUTPUTIMAGE_WINDOW "SuperpixelImage"

// Max threshhold of the trackbar
#define THRESHHOLD_MAX_VALUE 442

// Outputimage name and path
#define OUTPUTIMAGE_NAME "outputImage.jpg"
#define OUTPUTIMAGE_PATH "../Bilder/" OUTPUTIMAGE_NAME

#endif // COMMONDEFINES_H