cmake_minimum_required(VERSION 3.20)
project(HW2)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_STANDARD 14)

add_executable(HW2 main.cpp)
