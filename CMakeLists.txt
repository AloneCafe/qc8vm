cmake_minimum_required(VERSION 3.9)
project(qc8vm C)

set(CMAKE_C_STANDARD 99)

link_libraries(
        SDL2
        SDL2main
)

add_executable(
        qc8vm
        main.c
        main.h
        kernel.c
        kernel.h
        stack.c
        stack.h
        common.h
        renderer.c
        renderer.h
        timer.c
        timer.h
        keyboard.c
        keyboard.h
        opcode.c
        opcode.h
        debug.c debug.h)