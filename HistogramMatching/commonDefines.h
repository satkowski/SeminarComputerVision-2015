#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_INPUTIMAGE_1_STRING "img1"
#define ARGUMENT_INPUTIMAGE_2_STRING "img2"
#define ARGUMENT_COLOUR_STRING "colour"
// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_INPUTIMAGE_1_LIST ARGUMENT_INPUTIMAGE_1_STRING " input1"
#define ARGUMENT_INPUTIMAGE_2_LIST ARGUMENT_INPUTIMAGE_2_STRING " input2"
#define ARGUMENT_COLOUR_LIST ARGUMENT_COLOUR_STRING " color col c"

// Name of the Windows
#define INPUTIMAGE_1_WINDOW "InputImage 2"
#define INPUTIMAGE_2_WINDOW "InputImage 2"
#define OUTPUTIMAGE_WINDOW "OutputImage"

// Outputimage name and path
#define OUTPUTIMAGE_NAME "outputImage_HistogrammMatch.jpg"
#define OUTPUTIMAGE_PATH "../Bilder/Output/" OUTPUTIMAGE_NAME

#endif // COMMONDEFINES_H