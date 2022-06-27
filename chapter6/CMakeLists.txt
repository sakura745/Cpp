cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  17)

add_executable(fundamentalFunction fundamentalFunction.cpp)
add_executable(functionParameter functionParameter.cpp)
add_executable(twoParaMain twoParaMain.cpp)
add_executable(function function.cpp)
add_executable(functionReturnType functionReturnType.cpp)
add_executable(functionOverload functionOverload.cpp)
add_executable(nameLookup nameLookup.cpp)


