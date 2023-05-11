cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  17)

add_executable(iostream iostream.cc)
add_executable(in_Output in_Output.cc)
add_executable(fileStream fileStream.cc)
add_executable(memoryStream memoryStream.cc)




add_executable(iostate iostate.cc)
add_executable(iolocate iolocate.cc)
add_executable(ioSync ioSync.cc)