#!/bin/bash

mkdir -p build/intermediate
cd build/intermediate
cmake ../../src # Generate g++ makefile
make            # Build using g++
