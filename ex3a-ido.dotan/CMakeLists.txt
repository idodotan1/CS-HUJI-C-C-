cmake_minimum_required(VERSION 3.22)
project(ex3a_ido_dotan C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex3a_ido_dotan
        linked_list.c
        markov_chain.c
        tweets_generator.c
        tests.c)
