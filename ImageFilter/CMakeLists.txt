cmake_minimum_required(VERSION 2.8)
project( ImageFilter )

find_package( OpenCV REQUIRED )

add_executable( ImageFilter main.cpp filters.cpp )

target_link_libraries( ImageFilter ${OpenCV_LIBS} )