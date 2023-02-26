cmake_minimum_required(VERSION 3.24)
project(Sergei-Pirat-2009-mp3)

set(CMAKE_C_STANDARD 99)
add_subdirectory(mylib)

add_executable(Sergei-Pirat-2009-mp3 1laba/main.c)
target_link_libraries(Sergei-Pirat-2009-mp3 1laba/mylib)
