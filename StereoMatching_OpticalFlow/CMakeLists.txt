cmake_minimum_required(VERSION 2.8)
project( StereoMatching_OpticalFlow )

find_package( OpenCV REQUIRED )

add_executable( StereoMatching_OpticalFlow main.cpp opticalFlow.cpp )

target_link_libraries( StereoMatching_OpticalFlow ${OpenCV_LIBS} )