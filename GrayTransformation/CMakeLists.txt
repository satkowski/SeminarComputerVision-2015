cmake_minimum_required(VERSION 2.8)
project( GrayTransformation )

find_package( OpenCV REQUIRED )

add_executable( GrayTransformation main.cpp transformations.cpp )

target_link_libraries( GrayTransformation${OpenCV_LIBS} )