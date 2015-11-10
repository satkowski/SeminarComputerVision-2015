cmake_minimum_required(VERSION 2.8)
project( CrossCorrelation )

find_package( OpenCV REQUIRED )

add_executable( CrossCorrelation main.cpp crossCorrelation.cpp )

target_link_libraries( CrossCorrelation ${OpenCV_LIBS} )