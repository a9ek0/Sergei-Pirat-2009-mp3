cmake_minimum_required(VERSION 3.23)
project(decompressor C)

set(CMAKE_C_STANDARD 99)

add_executable(decompressor main.c functions.c)
