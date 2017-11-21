cmake_minimum_required(VERSION 3.6)
project(argument_parser)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(argument_parser src/argument_parser.cpp)