cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD  17)

add_executable(initialization initialization.cpp)
add_executable(type type.cpp)
add_executable(type2 type2.cpp)
add_executable(variable variable.cpp)
add_executable(typeConversion typeConversion.cpp)
add_executable(pointer pointer.cpp)
add_executable(reference reference.cpp)
add_executable(constConstexpr constConstexpr.cpp)
add_executable(typeAlias typeAlias.cpp)
add_executable(autoDeduction autoDeduction.cpp)
add_executable(scope scope.cpp)






