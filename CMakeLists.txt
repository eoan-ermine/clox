cmake_minimum_required(VERSION 3.5)

project (clox)

set(SOURCES
    clox/chunk.c
    clox/debug.c
    clox/main.c
    clox/memory.c
    clox/rle.c
    clox/value.c
)

add_executable(clox ${SOURCES})