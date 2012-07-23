# Main Project Configuration
cmake_minimum_required(VERSION 2.8.7)
project(ctu)

set(RUNTIME_OUTPUT_DIRECTORY ../foo)
add_executable(ctu ctu/main.cpp)