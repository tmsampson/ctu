#!/bin/bash
CTU_ROOT_DIR=$PWD
CTU_BUILD_DIR=$CTU_ROOT_DIR/build
CTU_INTERMEDIATE_DIR=$CTU_BUILD_DIR/intermediate
CTU_TEST_RESOURCES_DIR=$CTU_ROOT_DIR/src/ctutest/ctutest_resources

function exit_if_failed
{
	# Exit early if previous command failed
	if ! (( $? == 0 )); then
	cd ../../ # Return to original directory
	exit
	fi
}

# Create and move to intermediate build directory
mkdir -p $CTU_INTERMEDIATE_DIR
cd $CTU_INTERMEDIATE_DIR

# Generate ctu g++ makefile
cmake $CTU_ROOT_DIR/src
exit_if_failed

# Build ctu using g++
make
exit_if_failed

# Run unit tests
clear
echo =====================================================
echo = R U N N I N G = U N I T = T E S T S
echo =====================================================
cd $CTU_BUILD_DIR
mkdir $CTU_BUILD_DIR/ctutest_resources
cp -r $CTU_TEST_RESOURCES_DIR/* $CTU_BUILD_DIR/ctutest_resources
./ctutest
rm -r $CTU_BUILD_DIR/ctutest_resources

# Return to original directory
cd $CTU_ROOT_DIR
