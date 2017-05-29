cmake_minimum_required(VERSION 3.6)
project(kursach)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Matrix.cpp Matrix.hpp)
add_executable(kursach ${SOURCE_FILES})
