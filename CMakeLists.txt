cmake_minimum_required(VERSION 3.13)
project(Vector)

set(CMAKE_CXX_STANDARD 14)

add_executable(Vector main.cpp NewVector/vector.cpp NewVector/vector.h)
