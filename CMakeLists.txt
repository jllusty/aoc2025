cmake_minimum_required(VERSION 4.1)

project(AdventOfCode2025
    DESCRIPTION "Advent of Code 2025 Solutions"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Day1 1/main.cpp)
