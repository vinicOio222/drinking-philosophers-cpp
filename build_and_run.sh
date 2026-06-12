#!/bin/bash
# Build script for the Drinking Philosophers project

# Create build directory if it doesn't exist
mkdir -p build

# Change to the build directory
cd build
cmake ..
cmake --build .

# Copy test case files to build directory
cp ../src/cases/case1.txt .
cp ../src/cases/case2.txt .
cp ../src/cases/case3.txt .

# Run the executable
./Debug/drinking-philosophers-cpp

# Copy results to project root
cp results.txt ../results.txt

# Return to the original directory
cd ..
