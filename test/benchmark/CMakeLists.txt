cmake_minimum_required(VERSION 3.17)
project(ACLibrary)

set(GOOGLETEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../unittest/googletest")

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wshadow -Wconversion)

add_subdirectory(benchmark)

include_directories(.)
include_directories(../../)

add_executable(modint_raw modint_raw.cpp)
target_link_libraries(modint_raw benchmark::benchmark)

add_executable(vector_resize vector_resize.cpp)
target_link_libraries(vector_resize benchmark::benchmark)
