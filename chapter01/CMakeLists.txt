cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD  20)

add_executable(main main.cpp)
add_executable(annotations annotations.cc)
add_executable(c-styleCpp c-styleCpp.cpp)
add_executable(io io.cpp)
add_executable(namespace namespace.cpp)
add_executable(struct struct.cpp)


