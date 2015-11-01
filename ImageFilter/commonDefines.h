#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_INPUTIMAGE_STRING "img"
#define ARGUMENT_FILTERSELECTION_STRING "filter"
// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_INPUTIMAGE_LIST ARGUMENT_INPUTIMAGE_STRING " input"
#define ARGUMENT_FILTERSELECTION_LIST ARGUMENT_FILTERSELECTION_STRING " flt f"

// Name of the Windows
#define INPUTIMAGE_WINDOW "InputImage 1"
#define OUTPUTIMAGE_WINDOW "OutputImage"

// Outputimage name and path
#define OUTPUTIMAGE_UNSHARP_NAME "outputImage_Unsharp.jpg"
#define OUTPUTIMAGE_MEDIAN_NAME "outputImage_Filter.jpg"
#define OUTPUTIMAGE_MEDIAN_PATH "../Bilder/Output/" OUTPUTIMAGE_MEDIAN_NAME
#define OUTPUTIMAGE_UNSHARP_PATH "../Bilder/Output/" OUTPUTIMAGE_UNSHARP_NAME

#endif // COMMONDEFINES_H