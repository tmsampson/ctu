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

##############################################################
# Packaging Configuration                                    #
##############################################################
# To generate install package...                             #
# Windows: 'make_windows package'                            #
# Linux:   './make_linux package'                            #
# OSX:     './make_osx package'                              #
# Note: Resulting package is placed in ${CTU_ROOT}/package   #
##############################################################
set(CPACK_OUTPUT_FILE_PREFIX "${CTU_ROOT}/package")
set(CPACK_PACKAGE_NAME "ctu")
set(CPACK_PACKAGE_CONTACT "Thomas Sampson <drummertom999@gmail.com>")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 1)
set(CPACK_PACKAGE_VERSION_STRING "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_FILE_NAME "ctu-${CPACK_PACKAGE_VERSION_STRING}-${CMAKE_SYSTEM_NAME}-x86")
STRING(TOLOWER ${CPACK_PACKAGE_FILE_NAME} CPACK_PACKAGE_FILE_NAME)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CTU Command-line Task Utility")
set(CPACK_PACKAGE_DESCRIPTION "Manage task lists with ease without leaving the command line environment")

if(WIN32 OR APPLE)
      # Zip archive specifics
      install(TARGETS ctu DESTINATION .)
      install(FILES "${CTU_ROOT}/README.rst" DESTINATION .)
      set(CPACK_GENERATOR "ZIP")
endif()

if(UNIX AND NOT APPLE)
      # Debian (.deb) specifics
      install(TARGETS ctu DESTINATION bin)
      install(FILES "${CTU_ROOT}/README.rst" DESTINATION share/doc/ctu)
      set(CPACK_GENERATOR "DEB")
      set(CPACK_DEBIAN_PACKAGE_SECTION 'utils')
      set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION})
endif()

include(CPack)