cmake_minimum_required(VERSION 3.10)
project(arcsc C)

file(GLOB SRC_FILES src/*.c src/parser/*.c src/vm/*.c src/runtime/*.c)

add_executable(arcsc ${SRC_FILES})
