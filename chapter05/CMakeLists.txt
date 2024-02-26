cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  17)

add_executable(statement statement.cpp)
add_executable(branchStatement branchStatement.cpp)
add_executable(loopStatement loopStatement.cpp)
add_executable(breakContinue breakContinue.cpp)
add_executable(DuffsDevice DuffsDevice.cpp)
add_executable(veriDuffsDevice veriDuffsDevice.cc)