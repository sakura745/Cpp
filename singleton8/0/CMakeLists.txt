cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_BUILD_TYPE "release")
set(CMAKE_CXX_STANDARD 17)

add_executable(singleton8 sing.cpp main.cpp)