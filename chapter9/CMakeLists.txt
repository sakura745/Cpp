cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  17)


add_executable(iterator iterator.cc)
add_executable(array array.cc)
add_executable(vector vector.cc)
add_executable(otherSequenceContainer otherSequenceContainer.cc)