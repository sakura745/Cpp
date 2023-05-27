cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  17)

add_executable(array array.cpp)
add_executable(arrayPointer arrayPointer.cpp)
add_executable(arrayData arrayData.cpp)
add_executable(arrayOperate arrayOperate.cpp)
add_executable(cString cString.cpp)
add_executable(multi-dimensionArray multi-dimensionArray.cpp)
add_executable(Vector Vector.cpp)
add_executable(String String.cpp)
