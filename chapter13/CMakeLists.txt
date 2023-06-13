cmake_minimum_required(VERSION 3.25)

project(project)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")



add_executable(functionTemplate functionTemplate.cc)
add_executable(functionTemplate2 functionTemplate2.cc source.cc)
add_executable(classTemplate classTemplate.cc)
add_executable(concepts concepts.cc)