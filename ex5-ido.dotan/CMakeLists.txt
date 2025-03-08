cmake_minimum_required(VERSION 3.22)
project(ex5_ido_dotan)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_ido_dotan
        Movie.cpp
        Movie.h
        RecommendationSystem.h
        RecommendationSystemLoader.cpp
        RecommendationSystemLoader.h
        User.h
        UsersLoader.cpp
        UsersLoader.h
        User.cpp
        RecommendationSystem.cpp)
