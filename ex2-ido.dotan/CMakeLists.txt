cmake_minimum_required(VERSION 3.22)
project(ex2_ido_dotan C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex2_ido_dotan
        main.c
        sort_bus_lines.c
        sort_bus_lines.h
        test_bus_lines.c
        test_bus_lines.h)
