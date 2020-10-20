cmake_minimum_required(VERSION 3.15)
project(silo-newc CXX)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)
add_subdirectory(src)
target_link_libraries(silo-newc Threads::Threads)
