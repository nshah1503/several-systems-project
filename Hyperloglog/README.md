# HyperLogLog Cardinality Estimator

A C++ implementation of the HyperLogLog algorithm for estimating the cardinality (number of unique elements) of large datasets with high accuracy and low memory usage.

## Features

- **High Precision**: Configurable precision bits (1-16) for accuracy vs memory trade-off
- **Memory Efficient**: Uses only a few KB of memory regardless of dataset size
- **Fast**: O(1) time complexity for adding elements
- **Robust Testing**: Comprehensive test suite with various data distributions
- **Easy to Use**: Simple command-line interface with demo mode

## Build Pipeline

### Quick Start
```bash
# Run the complete build pipeline (build + test + usage instructions)
./build.sh
```

### Manual Build
```bash
# Create and navigate to build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run tests
ctest --output-on-failure
```

## Usage

### Main Application (`./hyperloglog`)

```bash
# Show usage information
./hyperloglog --help

# Run demo with various examples
./hyperloglog --demo

# Custom test with specific parameters
./hyperloglog [precision_bits] [num_elements]
./hyperloglog 4 1000    # Precision=4, 1000 elements
./hyperloglog 6 10000   # Precision=6, 10000 elements
```

### Test Suite (`./test_hyperloglog`)

```bash
# Run comprehensive test suite
./test_hyperloglog

# Run tests with CTest
ctest --output-on-failure
ctest --verbose
```

## Test Scenarios

The test suite includes:

1. **Normal Distribution**: Many repeated numbers around a mean
2. **Zipf Distribution**: Power law distribution (common in real-world data)
3. **Clustered Distribution**: Hotspots with frequent repeats
4. **Exponential Distribution**: Many small numbers, few large ones
5. **Mixed Distribution**: Combination of unique and repeated elements
6. **Edge Cases**: All identical elements

## Project Structure

```
project2/
├── src/
│   ├── main.cpp              # Main application entry point
│   └── hyperloglog.cpp       # HyperLogLog implementation
├── include/
│   └── hyperloglog.h         # Header file
├── test/
│   └── test_hyperloglog.cpp  # Comprehensive test suite
├── build.sh                  # Build pipeline script
├── CMakeLists.txt           # CMake configuration
└── README.md                # This file
```

## Algorithm Details

HyperLogLog estimates cardinality using:
- Hash function to distribute elements uniformly
- Leading zero counting in hash values
- Harmonic mean for final estimation
- Bias correction for small and large ranges

## Precision vs Memory

| Precision Bits | Registers | Memory Usage | Relative Error |
|----------------|-----------|--------------|----------------|
| 4              | 16        | ~16 bytes    | ~26%           |
| 6              | 64        | ~64 bytes    | ~13%           |
| 8              | 256       | ~256 bytes   | ~6.5%          |
| 10             | 1024      | ~1 KB        | ~3.25%         |
| 12             | 4096      | ~4 KB        | ~1.625%        |

## Examples

### Demo Output
```bash
$ ./hyperloglog --demo
=== HyperLogLog Demo ===

--- Demo 1: Simple Test ---
Added 100 unique elements
Estimated cardinality: 98.5

--- Demo 2: Test with Duplicates ---
Added 500 elements from only 50 unique values
Estimated cardinality: 52.3

--- Demo 3: Large Dataset ---
Added 10,000 unique elements
Estimated cardinality: 9876.2
```

### Custom Test
```bash
$ ./hyperloglog 6 5000
=== Custom HyperLogLog Test ===
Precision bits: 6
Number of elements: 5000
Added 5000 elements
Estimated cardinality: 4876.8
```

## Building from Source

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler
- Make or Ninja build system

### Build Commands
```bash
# Using the build script (recommended)
./build.sh

# Manual build
mkdir build && cd build
cmake ..
make
```

## Testing

The project includes comprehensive tests that run automatically during the build process:

```bash
# Run tests manually
./test_hyperloglog

# Run tests with CTest
ctest --output-on-failure

# Run specific test
ctest -R HyperLogLog_Tests
```