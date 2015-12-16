cmake_minimum_required(VERSION 2.8)
project( HomographyImageTransformation )

find_package( OpenCV REQUIRED )

add_executable( CrossCorrelation main.cpp )

target_link_libraries( HomographyImageTransformation ${OpenCV_LIBS} )