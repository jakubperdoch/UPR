cmake_minimum_required(VERSION 4.0)
project(sdl C)

set(CMAKE_C_STANDARD 11)

add_executable(sdl main.c
        array.h
        array.c)
