cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD  17)

add_executable(init init.cpp)
add_executable(type1 type1.cpp)
add_executable(type2 type2.cpp)
