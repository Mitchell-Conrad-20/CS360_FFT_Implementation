cmake_minimum_required(VERSION 3.16)   # CMake version check
project(Exam03Print_Sp24)               
set(CMAKE_CXX_STANDARD 11)             # Enable c++11 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Main
set(SOURCE_FILES FFT.cpp Utilities.h)
add_executable(Exam03Print ${SOURCE_FILES})


