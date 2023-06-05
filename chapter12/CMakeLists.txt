cmake_minimum_required(VERSION 3.16)

project(project)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")


add_executable(operatorOverload operatorOverload.cc)
add_executable(operatorOverload2 operatorOverload2.cc)
add_executable(inheritance inheritance.cc)
add_executable(inheritance2 inheritance2.cc)
add_executable(virtualFunction virtualFunction.cc)
add_executable(virtualFunction2 virtualFunction2.cc)
add_executable(specialFunction specialFunction.cc)