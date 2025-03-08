cmake_minimum_required(VERSION 3.22)
project(ex2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex2
        cipher.c
        cipher.h
        main.c
        tests.c
        tests.h)
