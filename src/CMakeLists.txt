# Main Project Configuration
project(ctu)
cmake_minimum_required(VERSION 2.8.7)
set(CTU_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(EXECUTABLE_OUTPUT_PATH ${CTU_ROOT}/build)
set(LIBRARY_OUTPUT_PATH ${CTU_ROOT}/build)

# Build Google Test Framework (libgtest)
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

# Build jsoncpp (libjsoncpp)
set(JSON_ROOT "third_party/jsoncpp")
include_directories("${JSON_ROOT}")
include_directories("${JSON_ROOT}/include")
add_library(jsoncpp STATIC
            ${JSON_ROOT}/src/json_reader.cpp
            ${JSON_ROOT}/src/json_value.cpp
            ${JSON_ROOT}/src/json_writer.cpp)
set_target_properties(jsoncpp PROPERTIES PREFIX "lib")

# Build ctulib
set(CTULIB_ROOT "ctulib")
include_directories("${CTULIB_ROOT}")
include_directories("${CTULIB_ROOT}/include")
add_library(ctulib STATIC
            ${CTULIB_ROOT}/src/ctulib.cpp)
target_link_libraries(ctulib jsoncpp)

# Build ctutest unit tests
if(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif(CMAKE_COMPILER_IS_GNUCXX)
add_executable(ctutest ctutest/ctutest.cpp)
target_link_libraries(ctutest ctulib gtest)

# Build main ctu executable
add_executable(ctu ctu/main.cpp)
target_link_libraries(ctu ctulib)