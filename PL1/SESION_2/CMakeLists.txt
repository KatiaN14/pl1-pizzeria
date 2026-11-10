cmake_minimum_required(VERSION 4.3)
project(pl1_pizzeria)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(pl1_pizzeria
        main2.cpp
        pizzeria2.cpp
        pizzeria2.h
)