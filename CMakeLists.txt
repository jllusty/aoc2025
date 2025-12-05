cmake_minimum_required(VERSION 4.1)

project(AdventOfCode2025
    DESCRIPTION "Advent of Code 2025 Solutions"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Point compiler + linker to the Homebrew LLVM libc++
include_directories(/opt/homebrew/opt/llvm/include/c++/v1)
link_directories(/opt/homebrew/opt/llvm/lib/c++)

# Tell the compiler to use libc++
add_compile_options(-stdlib=libc++)
# Tell the linker to use libc++
add_link_options(-stdlib=libc++)

# Ensure rpath picks up Homebrew libc++ at runtime
add_link_options(-Wl,-rpath,/opt/homebrew/opt/llvm/lib/c++)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(NUM_DAYS 5)

foreach(day RANGE 1 ${NUM_DAYS})
    add_executable(Day${day} ${day}/main.cpp)
endforeach()
