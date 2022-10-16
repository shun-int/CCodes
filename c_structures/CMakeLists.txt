cmake_minimum_required(VERSION 3.23)
project(c_structures C)

set(CMAKE_C_STANDARD 99)

include_directories(        // header folder
        user
        inc
)

file(GLOB_RECURSE SOURCES   // source files
        "src/*.*"
        "user/*.*"
)

add_executable(c_structures
        user/main.c
        inc/queue.h
        src/queue.c
        inc/list.h
        src/list.c
        )
