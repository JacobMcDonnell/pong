cmake_minimum_required(VERSION 3.28)
project(pong C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror")

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

add_executable(pong main.c
        pong.c
        pong.h
        screen.c
        screen.h)

target_link_libraries(pong PRIVATE SDL2::SDL2)