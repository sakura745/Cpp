cmake_minimum_required(VERSION 3.16)

project(project)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD  20)


add_executable(struct struct.cc)
add_executable(memberFunction memberFunction.cc)
add_executable(access access.cc)
add_executable(constructorDestructor constructorDestructor.cc)
add_executable(constructorDestructor2 constructorDestructor2.cc)
add_executable(constructorDestructor3 constructorDestructor3.cc)
add_executable(constructorDestructor4 constructorDestructor4.cc)
add_executable(literal literal.cc)
add_executable(memberPointer memberPointer.cc)