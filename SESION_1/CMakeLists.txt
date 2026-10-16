cmake_minimum_required(VERSION 4.3)
project(pl1_pizzeria)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(pl1_pizzeria
        SESION_1/main.cpp
        SESION_1/pizzeria.cpp
        SESION_1/pizzeria.h)
