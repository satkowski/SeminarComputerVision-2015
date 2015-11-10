cmake_minimum_required(VERSION 2.8)
project( HistogramMatching )

find_package( OpenCV REQUIRED )

add_executable( HistogramMatching main.cpp histogramMatching.cpp )

target_link_libraries( HistogramMatching ${OpenCV_LIBS} )