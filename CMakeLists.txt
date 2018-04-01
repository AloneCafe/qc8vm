cmake_minimum_required(VERSION 3.9)
project(qc8vm C)

set(CMAKE_C_STANDARD 99)

link_libraries(SDL2 SDL2main)

add_executable(qc8vm main.c kernel.c kernel.h stack.c stack.h)