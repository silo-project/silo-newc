cmake_minimum_required(VERSION 3.15)
project(silo-newc CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER gcc)

add_subdirectory(src)
