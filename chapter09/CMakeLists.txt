cmake_minimum_required(VERSION 3.16)

project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  20)

add_executable(iterator iterator.cc)
add_executable(array array.cc)
add_executable(vector vector.cc)
add_executable(otherSequenceContainer otherSequenceContainer.cc)
add_executable(set set.cc)
add_executable(mapMultixxx mapMultixxx.cc)
add_executable(unordered_xxx unordered_xxx.cc)
add_executable(typeAdaptor typeAdaptor.cc)
add_executable(interfaceAdaptor interfaceAdaptor.cc)
add_executable(otherAdaptor otherAdaptor.cc)