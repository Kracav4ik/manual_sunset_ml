cmake_minimum_required(VERSION 3.5)
project(ms_ml)

add_definitions(-std=c++11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")  # F S A T

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(src)
