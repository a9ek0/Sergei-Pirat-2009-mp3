cmake_minimum_required(VERSION 3.23.2)
project(1laba C)

set(CMAKE_C_STANDARD 99)

add_executable(1laba main.c mylib/menu.c mylib/memory.c mylib/check.c mylib/parce.c mylib/sort.c mylib/structure.c)
