#!/bin/bash
# Build script for the Drinking Philosophers project (Linux version)

set -e  # Exit on error

# Create build directory if it doesn't exist
echo "Creating build directory..."
mkdir -p build

# Change to the build directory
cd build

# Build the project
echo "Building project..."
cmake ..
cmake --build .

# Copy test case files to build directory
echo "Copying test case files..."
cp ../src/cases/case1.txt .
cp ../src/cases/case2.txt .
cp ../src/cases/case3.txt .

# Run the executable
echo "Running the application..."
./drinking-philosophers-cpp

# Copy results to project root if they exist
if [ -f results.txt ]; then
    cp results.txt ../results.txt
    echo "Results copied to ../results.txt"
fi

# Return to the original directory
cd ..

echo "Build and run completed successfully!"
