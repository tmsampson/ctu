#!/bin/bash

function exit_if_failed
{
	# Exit early if previous command failed
	if ! (( $? == 0 )); then
	cd ../../ # Return to original directory
	exit
	fi
}

# Create and move to intermediate build directory
mkdir -p build/intermediate
cd build/intermediate

# Generate ctu g++ makefile
cmake ../../src
exit_if_failed

# Build ctu using g++
make
exit_if_failed

# Run unit tests
clear
echo =====================================================
echo = R U N N I N G = U N I T = T E S T S
echo =====================================================
cd ../
mkdir unit_test_resources
./ctutest
rm -r unit_test_resources

# Return to original directory
cd ../
