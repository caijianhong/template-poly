cmake_minimum_required(VERSION 3.17)
project(PolyLibrary)


if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    message("Not MSVC")
    add_compile_options(-Wall -Wextra -Wshadow -Wconversion -O0)
    add_compile_options(-fsanitize=undefined,address -fno-sanitize-recover=all)
    add_link_options(-fsanitize=undefined,address)
else()
    message("Use MSVC")
    add_compile_options(/W4 /permissive- /sdl)
endif()

enable_testing()

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

include_directories(.)
include_directories(../../)

add_executable(modint modint.cpp)

add_executable(internal_math internal_math.cpp)

add_executable(multiple multiple.cpp)
target_link_libraries(multiple gtest gtest_main)
gtest_discover_tests(multiple)
