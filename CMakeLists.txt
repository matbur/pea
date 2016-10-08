cmake_minimum_required(VERSION 3.6)
project(pea)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp File.cpp File.h)
add_executable(pro ${SOURCE_FILES})
