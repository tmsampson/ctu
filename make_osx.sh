#!/bin/bash
CTU_ROOT_DIR=$PWD
CTU_BUILD_DIR=$CTU_ROOT_DIR/build

function exit_if_failed
{
	# Exit early if previous command failed
	if ! (( $? == 0 )); then
	cd ../../ # Return to original directory
	exit
	fi
}

# For now the linux build works just fine
sh make_linux.sh
exit_if_failed

# Build package?
if [ "$1" == package ]; then
	printf "\r\n"
	echo =====================================================
	echo = G E N E R A T I N G = Z I P = P A C K A G E
	echo =====================================================
	cd $CTU_BUILD_DIR/intermediate
	cpack -G ZIP
fi
