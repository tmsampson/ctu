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

# Return to original directory
cd ../../