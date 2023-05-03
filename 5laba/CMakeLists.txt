cmake_minimum_required(VERSION 3.23)
project(5laba C)

set(CMAKE_C_STANDARD 99)

add_executable(5laba main.c lyb/menu.c lyb/cache.c lyb/checks.c lyb/memory.c lyb/other.c)

add_executable(ip_test ip_test.c)