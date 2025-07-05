#include "../include/hyperloglog.h"
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Test scenario 1: Many repeated numbers with normal distribution
void testRepeatedNumbers() {
    cout << "\n=== Test 1: Many Repeated Numbers ===" << endl;
    Hyperloglog(4);
    
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> normal_dis(500, 100); // Mean=500, Std=100
    
    // Generate numbers with many repeats
    for (int i = 0; i < 2000; i++) {
        int num = max(0, min(1000, (int)normal_dis(gen))); // Clamp to 0-1000
        string element = "element_" + to_string(num);
        AddElement(element);
    }
    
    cout << "Added 2000 elements with normal distribution (many repeats expected)" << endl;
    GetCardinality();
}

// Test scenario 2: Zipf distribution (power law) - many small numbers, few large ones
void testZipfDistribution() {
    cout << "\n=== Test 2: Zipf Distribution (Power Law) ===" << endl;
    Hyperloglog(4);
    
    random_device rd;
    mt19937 gen(rd());
    
    // Zipf-like distribution: probability of number i is proportional to 1/i
    vector<int> numbers;
    for (int i = 1; i <= 100; i++) {
        int count = 1000 / i; // More repeats for smaller numbers
        for (int j = 0; j < count; j++) {
            numbers.push_back(i);
        }
    }
    
    // Shuffle to avoid bias
    shuffle(numbers.begin(), numbers.end(), gen);
    
    for (int num : numbers) {
        string element = "element_" + to_string(num);
        AddElement(element);
    }
    
    cout << "Added " << numbers.size() << " elements with Zipf distribution" << endl;
    GetCardinality();
}

// Test scenario 3: Clustered distribution with hotspots
void testClusteredDistribution() {
    cout << "\n=== Test 3: Clustered Distribution with Hotspots ===" << endl;
    Hyperloglog(4);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 999);
    
    // Create hotspots where certain numbers appear much more frequently
    vector<int> hotspots = {42, 123, 456, 789, 999};
    map<int, int> hotspot_weights = {{42, 50}, {123, 30}, {456, 40}, {789, 25}, {999, 35}};
    
    for (int i = 0; i < 1500; i++) {
        int num;
        if (dis(gen) < 200) { // 20% chance to pick from hotspots
            int hotspot_idx = dis(gen) % hotspots.size();
            num = hotspots[hotspot_idx];
        } else {
            num = dis(gen);
        }
        
        string element = "element_" + to_string(num);
        AddElement(element);
        
        // Add extra repeats for hotspots
        if (hotspot_weights.find(num) != hotspot_weights.end()) {
            for (int j = 0; j < hotspot_weights[num]; j++) {
                AddElement(element);
            }
        }
    }
    
    cout << "Added elements with clustered distribution and hotspots" << endl;
    GetCardinality();
}

// Test scenario 4: Exponential distribution with many small numbers
void testExponentialDistribution() {
    cout << "\n=== Test 4: Exponential Distribution ===" << endl;
    Hyperloglog(4);
    
    random_device rd;
    mt19937 gen(rd());
    exponential_distribution<> exp_dis(0.01); // Lambda = 0.01
    
    for (int i = 0; i < 2500; i++) {
        int num = min(1000, (int)exp_dis(gen)); // Clamp to 0-1000
        string element = "element_" + to_string(num);
        AddElement(element);
    }
    
    cout << "Added 2500 elements with exponential distribution" << endl;
    GetCardinality();
}

// Test scenario 5: Mixed distribution with different patterns
void testMixedDistribution() {
    cout << "\n=== Test 5: Mixed Distribution ===" << endl;
    Hyperloglog(4);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 999);
    
    // Phase 1: Many unique numbers
    for (int i = 0; i < 500; i++) {
        string element = "unique_" + to_string(i);
        AddElement(element);
    }
    
    // Phase 2: Many repeated numbers
    for (int i = 0; i < 1000; i++) {
        int num = dis(gen) % 50; // Only 50 different numbers, many repeats
        string element = "repeat_" + to_string(num);
        AddElement(element);
    }
    
    // Phase 3: Some unique, some repeated
    for (int i = 0; i < 500; i++) {
        if (dis(gen) < 300) { // 60% chance of repeat
            int num = dis(gen) % 100;
            string element = "mixed_" + to_string(num);
            AddElement(element);
        } else {
            string element = "mixed_unique_" + to_string(1000 + i);
            AddElement(element);
        }
    }
    
    cout << "Added mixed distribution: unique + repeated + mixed" << endl;
    GetCardinality();
}

// Test scenario 6: Edge case - all same number
void testAllSameNumber() {
    cout << "\n=== Test 6: All Same Number (Edge Case) ===" << endl;
    Hyperloglog(4);
    
    for (int i = 0; i < 1000; i++) {
        string element = "same_number_42";
        AddElement(element);
    }
    
    cout << "Added 1000 identical elements" << endl;
    GetCardinality();
}

int main() {
    cout << "Running comprehensive HyperLogLog tests with various distributions..." << endl;
    
    testRepeatedNumbers();
    testZipfDistribution();
    testClusteredDistribution();
    testExponentialDistribution();
    testMixedDistribution();
    testAllSameNumber();
    
    cout << "\n=== All tests completed ===" << endl;
    return 0;
} 