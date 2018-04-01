cmake_minimum_required(VERSION 3.9)
project(quickchip8_kernel C)

set(CMAKE_C_STANDARD 99)

link_libraries(SDL2 SDL2main)

add_executable(quickchip8_kernel main.c kernel.c kernel.h stack.c stack.h)