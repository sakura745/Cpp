cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_BUILD_TYPE "release")
set(CMAKE_CXX_STANDARD 20)

add_executable(singleton1 sing.cpp main.cpp)