cmake_minimum_required(VERSION 3.17)
project(PolyLibrary)


if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    message("Not MSVC")
    add_compile_options(-Wall -Wextra -Wshadow -Wconversion -O0 -g)
    add_compile_options(-fsanitize=undefined,address -fno-sanitize-recover=all)
    add_link_options(-fsanitize=undefined,address)
else()
    message("Use MSVC")
    add_compile_options(/W4 /permissive- /sdl)
endif()

include_directories(.)
include_directories(../../)

add_executable(getinv getinv.cpp)
add_executable(LOJ150 LOJ150.cpp)
add_executable(multiple multiple.cpp)
add_executable(getexp getexp.cpp)
add_executable(test test.cpp)
add_executable(linear_rec linear_rec.cpp)
add_executable(divide divide.cpp)
