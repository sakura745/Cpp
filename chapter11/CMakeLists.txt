cmake_minimum_required(VERSION 3.16)

project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  20)


add_executable(struct struct.cc)
add_executable(memberFunction memberFunction.cc)
add_executable(access access.cc)
add_executable(constructorDestructor constructorDestructor.cc)
add_executable(constructorDestructor2 constructorDestructor2.cc)