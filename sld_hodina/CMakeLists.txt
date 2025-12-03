cmake_minimum_required(VERSION 3.10)
project(MySDLProject)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(myapp
        atoms.c
        sdl_playground.c)
target_include_directories(myapp PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(myapp ${SDL2_LIBRARIES})