cmake_minimum_required(VERSION 3.10)
project(snow C)

set(CMAKE_C_STANDARD 11)

include_directories(/opt/homebrew/include /opt/homebrew/include/SDL2)
link_directories(/opt/homebrew/lib)

add_executable(snow main.c
        dynamic_array.h
        dynamic_array.c
        sdl.h
        sdl.c)

target_link_libraries(snow SDL2 SDL2_image SDL2_gfx)