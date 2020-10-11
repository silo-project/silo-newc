cmake_minimum_required(VERSION 3.15)
project(silo-newc C)

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_C_STANDARD 11)

add_executable(silo-newc
silo.c
silo_gate.c
silo_node.c
silo_nodeconf.c
silo_recycle.c
silo_signal.c
silo_simulate.c
)
