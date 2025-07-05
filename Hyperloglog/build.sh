#!/bin/bash

# HyperLogLog Build and Test Pipeline
# This script builds the project, runs tests, and provides usage instructions

set -e  # Exit on any error

echo "=== HyperLogLog Build Pipeline ==="
echo

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# Navigate to build directory
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..

# Build the project
echo "Building project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo
echo "=== Build Complete ==="
echo

# Run tests automatically
echo "=== Running Tests ==="
ctest --output-on-failure

echo
echo "=== Test Results ==="
echo "Tests completed successfully!"

echo
echo "=== Usage Instructions ==="
echo "Main application:"
echo "  ./hyperloglog --help          # Show usage information"
echo "  ./hyperloglog --demo          # Run demo with various examples"
echo "  ./hyperloglog 4 1000          # Custom test with precision=4, 1000 elements"
echo
echo "Run tests manually:"
echo "  ./test_hyperloglog            # Run comprehensive test suite"
echo
echo "Run tests with CTest:"
echo "  ctest --output-on-failure     # Run tests with detailed output"
echo "  ctest --verbose               # Run tests with verbose output"
echo

echo "=== Build Pipeline Complete ==="
echo "You can now use ./hyperloglog for your main application!" 