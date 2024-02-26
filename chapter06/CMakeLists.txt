cmake_minimum_required(VERSION 3.19)
project(project)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD  20)

add_executable(fundamentalFunction fundamentalFunction.cpp)
add_executable(functionParameter functionParameter.cpp)
add_executable(twoParaMain twoParaMain.cpp)
add_executable(function function.cpp)
add_executable(functionReturnType functionReturnType.cpp)
add_executable(functionOverload functionOverload.cpp)
add_executable(nameLookup nameLookup.cpp)
add_executable(nonviableCandidates nonviableCandidates.cpp)

add_executable(inlineFunction inlineMain.cpp inlineSource.cpp)

add_executable(constexpr constexpr.cpp)
add_executable(consteval consteval.cc)
add_executable(functionPointer functionPointer.cpp)



