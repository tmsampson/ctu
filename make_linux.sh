#!/bin/bash

# Create and move to intermediate build directory
mkdir -p build/intermediate
cd build/intermediate

# Generate ctu g++ makefile
cmake ../../src

# Exit early if cmake fails
if ! (( $? == 0 )); then
	# Return to original directory
	cd ../../
	exit
fi

# Build ctu using g++
make

# Run unit tests
clear
echo =====================================================
echo = R U N N I N G   U N I T   T E S T S
echo =====================================================
../ctutest

# Return to original directory
cd ../../
