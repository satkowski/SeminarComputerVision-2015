#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

// For parsing the values out of the commando line
#define ARGUMENT_HELP_STRING "help"
#define ARGUMENT_INPUTIMAGE_STRING "img"
#define ARGUMENT_TRANSFORMATION_STRING "transtype"
// The list of values that can activate certain things
#define ARGUMENT_HELP_LIST ARGUMENT_HELP_STRING " h usage ?"
#define ARGUMENT_INPUTIMAGE_LIST ARGUMENT_INPUTIMAGE_STRING " input"
#define ARGUMENT_TRANSFORMATION_LIST ARGUMENT_TRANSFORMATION_STRING " trans type tt"

// Name of the Windows
#define INPUTIMAGE_WINDOW "OriginalImage"
#define OUTPUTIMAGE_WINDOW "TransformedImage"

// Outputimage name and path
#define OUTPUTIMAGE_NAME "outputImage.jpg"
#define OUTPUTIMAGE_PATH "../Bilder/" OUTPUTIMAGE_NAME

#endif // COMMONDEFINES_H