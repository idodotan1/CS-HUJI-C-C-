cmake_minimum_required(VERSION 3.22)
project(ex4_ido_dotan)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_ido_dotan
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        main.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h)
