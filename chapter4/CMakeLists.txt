cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  17)

add_executable(expression expression.cpp)
add_executable(lvalrval lvalrval.cpp)
add_executable(typeConvert typeConvert.cpp)
add_executable(arithmeticOperator arithmeticOperator.cpp)
add_executable(logicOperator logicOperator.cpp)
