cmake_minimum_required(VERSION 2.8)
project( StereoMatching_Disparity )

find_package( OpenCV REQUIRED )

add_executable( StereoMatching_Disparity main.cpp stereoMatching.cpp postProcessing.cpp coloredPointCloud.cpp )

target_link_libraries( ImageFilter ${OpenCV_LIBS} )