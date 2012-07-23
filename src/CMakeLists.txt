# Main Project Configuration
cmake_minimum_required(VERSION 2.8.7)
project(ctu)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../)
add_executable(ctu ctu/main.cpp)
