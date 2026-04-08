cmake_minimum_required(VERSION 4.0)

set(CFLAGS -Wall -Wextra)
project(BrainfuckCompiler)
set(TARGET_EXE beefc)

add_executable(${TARGET_EXE}
    src/main.c
    src/brainfuck.h
    src/stack.h
    src/vector.h
    src/file_io.h
)

add_executable(test_target
    src/test.c
    src/brainfuck.h
    src/stack.h
    src/vector.h
    src/file_io.h
)