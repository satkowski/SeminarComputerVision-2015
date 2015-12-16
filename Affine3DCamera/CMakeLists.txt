cmake_minimum_required(VERSION 2.8)
project( Affine3DCamera )

find_package( OpenCV REQUIRED )

add_executable( CrossCorrelation main.cpp calculations.cpp )

target_link_libraries( Affine3DCamera ${OpenCV_LIBS} )