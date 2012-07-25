# Main Project Configuration
project(ctu)
cmake_minimum_required(VERSION 2.8.7)
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
set_target_properties(gtest PROPERTIES PREFIX "lib")

# Build ctutest unit tests
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(ctutest ctutest/ctutest.cpp)
target_link_libraries(ctutest gtest)

# Build main ctu executable
add_executable(ctu ctu/main.cpp)
