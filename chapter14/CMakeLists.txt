cmake_minimum_required(VERSION 3.25)

project(project)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")



add_executable(metaProgramming metaProgramming.cc)
add_executable(order order.cc)
add_executable(branch branch.cc)
add_executable(loop loop.cc)
add_executable(reduceInstantiation reduceInstantiation.cc)