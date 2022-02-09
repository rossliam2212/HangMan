cmake_minimum_required(VERSION 3.21)
project(HangMan)

set(CMAKE_CXX_STANDARD 14)

add_executable(HangMan src/main.cpp src/Dictionary.cpp src/Dictionary.h src/HangMan.cpp src/HangMan.h)
