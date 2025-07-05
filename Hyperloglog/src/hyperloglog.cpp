#include "iostream"
#include "../include/hyperloglog.h"
#include <cstdint>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <functional>
#include <set>

// Global variables for HyperLogLog
static vector<uint8_t> registers;  // Array of registers
static int b;                      // Number of bits used for bucket index
static int m;                      // Number of registers (2^b)

// Initialize HyperLogLog with b bits for bucket index
void Hyperloglog(int initial_bit) {
    b = initial_bit;
    m = 1 << b;  // 2^b
    registers.resize(m, 0);
}

bool kill_switch = true;
// Add an element to the HyperLogLog
void AddElement(const string& element) {
    hash_t hash_value;
    CalculateHash(element, hash_value);
    if (kill_switch) {
        std::cout << "hash_value: " << hash_value << std::endl;
        kill_switch = false; 
    }
    ComputeBinary(hash_value);
}

// Calculate hash value for a string
void CalculateHash(const string& element, hash_t& hash_value) {
    // Using std::hash for simplicity, but in practice you might want to use a better hash function
    hash<string> hasher;
    hash_value = hasher(element);
}


// Compute binary representation and update register
bool debug_switch = true;
void ComputeBinary(hash_t hash) {
    // Get bucket index from first b bits
    // std::cout << "b: " << b << std::endl;
    int bucket = hash & ((1 << b) - 1);
    // Get remaining bits for counting leading zeros
    hash_t remaining = hash >> b;
    // Find position of leftmost 1
    int position;
    PositionOfLeftMostOne(remaining, position);
    
    // Update register if new position is larger
    registers[bucket] = max(registers[bucket], static_cast<uint8_t>(position + 1));
}

// Find position of leftmost 1 in binary representation
void PositionOfLeftMostOne(hash_t hash, int& position) {
    if (hash == 0) {
        position = 64 - b;  // Maximum possible position
        return;
    }
    
    position = 0;
    while ((hash & 1) == 0) {
        hash >>= 1;
        position++;
    }
}

// Get cardinality estimate
void GetCardinality() {
    ComputeCardinality();
}

// Compute cardinality using HyperLogLog formula
void ComputeCardinality() {
    double sum = 0.0;
    for (int i = 0; i < m; i++) {
        sum += 1.0 / (1 << registers[i]);
    }
    
    double alpha = 0.7213 / (1 + 1.079 / m);  // Correction factor
    double estimate = alpha * m * m / sum;
    
    // Small range correction
    if (estimate < 2.5 * m) {
        int zeros = count(registers.begin(), registers.end(), 0);
        if (zeros != 0) {
            estimate = m * log(static_cast<double>(m) / zeros);
        }
    }
    
    // Large range correction
    if (estimate > (1.0 / 30.0) * (1ULL << 32)) {
        estimate = -(1ULL << 32) * log(1.0 - estimate / (1ULL << 32));
    }
    
    cout << "Estimated cardinality: " << estimate << endl;
}