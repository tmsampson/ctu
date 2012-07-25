# Main Project Configuration
cmake_minimum_required(VERSION 2.8.7)
project(ctu)
set(CTU_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(EXECUTABLE_OUTPUT_PATH ${CTU_ROOT}/build)
set(LIBRARY_OUTPUT_PATH ${CTU_ROOT}/build)

# Detection test
if(MSVC)
	MESSAGE("This is Windows")
elseif(CMAKE_COMPILER_IS_GNUCXX)
	MESSAGE("This is Linux")
endif()

# Build Google Test Framework
set(GTEST_ROOT "third_party/gtest")
include_directories("${GTEST_ROOT}")
include_directories("${GTEST_ROOT}/include")
add_library(gtest STATIC
            ${GTEST_ROOT}/src/gtest-typed-test.cc
            ${GTEST_ROOT}/src/gtest-death-test.cc
            ${GTEST_ROOT}/src/gtest-port.cc
            ${GTEST_ROOT}/src/gtest.cc
            ${GTEST_ROOT}/src/gtest-filepath.cc
            ${GTEST_ROOT}/src/gtest-test-part.cc)

# Build main ctu executable
add_executable(ctu ctu/main.cpp)