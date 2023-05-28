cmake_minimum_required(VERSION 3.16)

project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  20)

include_directories(/usr/lib/x86_64-linux-gnu/)#添加libtbb链接

add_executable(generic generic.cc)
target_link_libraries(generic libtbb.so)

add_executable(bind bind.cc)
add_executable(lambda1 lambda1.cc)
add_executable(lambda2 lambda2.cc)