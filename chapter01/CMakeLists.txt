cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD  17)

add_executable(io io.cpp)
add_executable(namespace namespace.cpp)
add_executable(c c.cpp)
add_executable(c1 c1.cpp)
add_executable(struct struct.cpp)