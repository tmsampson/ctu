# Main Project Configuration
project(ctu)
cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_BUILD_TYPE "Release")
set(CTU_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")

# Setup build output layout
if(MSVC)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "../")
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "../")
else()
      set(EXECUTABLE_OUTPUT_PATH ${CTU_ROOT}/build)
endif()

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

# Build libctu
set(LIBCTU_ROOT "libctu")
include_directories("${LIBCTU_ROOT}")
include_directories("${LIBCTU_ROOT}/include")
add_library(libctu STATIC
            ${LIBCTU_ROOT}/ConfigFile.cpp
            ${LIBCTU_ROOT}/Utils.cpp
            ${LIBCTU_ROOT}/CommandMgr.cpp
            ${LIBCTU_ROOT}/TaskList.cpp
            ${LIBCTU_ROOT}/CTU.cpp)
target_link_libraries(libctu jsoncpp)
if(MSVC)
      target_link_libraries(libctu shlwapi.lib)
endif()
set_target_properties(libctu PROPERTIES PREFIX "")

# Build ctutest unit tests
set(CTUTEST_ROOT "ctutest")
include_directories("${CTUTEST_ROOT}")
include_directories("${CTUTEST_ROOT}/include")
if(CMAKE_COMPILER_IS_GNUCXX)
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
add_executable(ctutest ${CTUTEST_ROOT}/ctutest.cpp)
target_link_libraries(ctutest libctu gtest)

# Build main ctu executable
add_executable(ctu ctu/main.cpp)
target_link_libraries(ctu libctu)