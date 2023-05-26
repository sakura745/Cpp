cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  20)



add_executable(dyMemory dyMemory.cc)
add_executable(smartPointer smartPointer.cc)
add_executable(others others.cc)