cmake_minimum_required(VERSION 2.8)
project( Superpixels )

find_package( OpenCV REQUIRED )

add_executable( Superpixels main.cpp helper.cpp )

target_link_libraries( Superpixels ${OpenCV_LIBS} )