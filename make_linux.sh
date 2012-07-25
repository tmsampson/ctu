#!/bin/bash

# Create and move to intermediate build directory
mkdir -p build/intermediate
cd build/intermediate

# Generate ctu g++ makefile
cmake ../../src

# Build ctu using g++
if (( $? == 0 )); then
make
fi

:: Run unit tests
clear
echo =====================================================
echo = R U N N I N G   U N I T   T E S T S
echo =====================================================
../ctutest

# Return to original directory
cd ../../
