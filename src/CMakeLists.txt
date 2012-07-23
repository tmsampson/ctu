# Main Project Configuration
cmake_minimum_required(VERSION 2.8.7)
project(ctu)

# Detection test
if(MSVC)
	MESSAGE("This is Windows")
elseif(CMAKE_COMPILER_IS_GNUCXX)
	MESSAGE("This is Linux")
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../)
add_executable(ctu ctu/main.cpp)
