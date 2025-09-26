cmake_minimum_required(VERSION 3.10)
project(arcsc C)

file(GLOB SRC_FILES src/*.c src/parser/*.c src/vm/*.c src/runtime/*.c src/runtime/global/*.c)

set(CMAKE_C_STANDARD 17)
link_directories(/usr/local/lib/)

add_executable(arcsc ${SRC_FILES})

target_compile_options(arcsc PRIVATE
    -I/usr/local/include/
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2 -mtune=native -march=x86-64-v2>
)

target_link_libraries(arcsc PRIVATE libffi.so)
