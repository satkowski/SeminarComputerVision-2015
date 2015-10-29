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

// Slidernames
#define SLIDER_ALPHA_NAME "Alpha * 0.2"
#define SLIDER_GAMMA_NAME "Gamma * 0.1"
#define SLIDER_OWN_NAME "Offset"
// Coefficent for the slidervalues
#define SLIDER_ALPHA_COEFFICENT 0.2
#define SLIDER_GAMMA_COEFFICENT 0.1
#define OWNTRANSFORMATION_OFFSET 30
// Slider Max Value
#define SLIDER_ALPHA_MAX_VALUE 100 / SLIDER_ALPHA_COEFFICENT
#define SLIDER_GAMMA_MAX_VALUE 100 / SLIDER_GAMMA_COEFFICENT
#define SLIDER_OWNTRANSFORMATION_MAX_VALUE 255 - OWNTRANSFORMATION_OFFSET

// Outputimage name and path
#define OUTPUTIMAGE_NAME "outputImage_GrayTransformation.jpg"
#define OUTPUTIMAGE_PATH "../Bilder/Output/" OUTPUTIMAGE_NAME

#endif // COMMONDEFINES_H