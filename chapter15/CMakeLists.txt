cmake_minimum_required(VERSION 3.25)

project(project)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")


add_executable(except except.cc)
add_executable(except2 except2.cc)
add_executable(except3 except3.cc)
add_executable(except4 except4.cc)
add_executable(enum enum.cc)
add_executable(union union.cc)
add_executable(nestClass nestClass.cc)
add_executable(nestNamespace nestNamespace.cc)
add_executable(bitFields bitFields.cc)