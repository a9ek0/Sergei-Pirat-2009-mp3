cmake_minimum_required(VERSION 3.24)
project(1laba C)

set(CMAKE_C_STANDARD 99)

add_executable(1laba main.c mylib/structure.c mylib/structure.h)
