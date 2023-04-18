cmake_minimum_required(VERSION 3.23)
project(4laba C)

set(CMAKE_C_STANDARD 99)


add_executable(4laba main.c lyb/menu.c lyb/tree.c lyb/check.c lyb/chrono.c lyb/memory.c lyb/query.c)

add_executable(213 213.c)