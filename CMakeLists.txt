cmake_minimum_required(VERSION 3.24)
project(Sergei-Pirat-2009-mp3)

include_directories(1laba/mylib)
set(CMAKE_C_STANDARD 99)

add_executable(Sergei-Pirat-2009-mp3 1laba/main.c)
target_include_directories(1laba/main.c PUBLIC 1laba/mylib)
