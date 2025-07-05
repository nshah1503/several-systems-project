#include "../include/hyperloglog.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

void printUsage() {
    cout << "HyperLogLog Cardinality Estimator" << endl;
    cout << "Usage:" << endl;
    cout << "  ./hyperloglog [precision_bits] [num_elements]" << endl;
    cout << "  ./hyperloglog --demo" << endl;
    cout << endl;
    cout << "Examples:" << endl;
    cout << "  ./hyperloglog 4 1000     # Precision=4, 1000 random elements" << endl;
    cout << "  ./hyperloglog --demo     # Run demo with various distributions" << endl;
}

void runDemo() {
    cout << "=== HyperLogLog Demo ===" << endl;
    
    // Demo 1: Simple test with known cardinality
    cout << "\n--- Demo 1: Simple Test ---" << endl;
    Hyperloglog(4);
    
    for (int i = 0; i < 100; i++) {
        string element = "unique_element_" + to_string(i);
        AddElement(element);
    }
    
    cout << "Added 100 unique elements" << endl;
    GetCardinality();
    
    // Demo 2: Test with duplicates
    cout << "\n--- Demo 2: Test with Duplicates ---" << endl;
    Hyperloglog(4);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 49); // Only 50 different numbers
    
    for (int i = 0; i < 500; i++) {
        int num = dis(gen);
        string element = "element_" + to_string(num);
        AddElement(element);
    }
    
    cout << "Added 500 elements from only 50 unique values" << endl;
    GetCardinality();
    
    // Demo 3: Large dataset
    cout << "\n--- Demo 3: Large Dataset ---" << endl;
    Hyperloglog(6); // Higher precision for larger dataset
    
    for (int i = 0; i < 10000; i++) {
        string element = "large_dataset_" + to_string(i);
        AddElement(element);
    }
    
    cout << "Added 10,000 unique elements" << endl;
    GetCardinality();
}

void runCustomTest(int precision, int numElements) {
    cout << "=== Custom HyperLogLog Test ===" << endl;
    cout << "Precision bits: " << precision << endl;
    cout << "Number of elements: " << numElements << endl;
    
    Hyperloglog(precision);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, numElements * 2); // Some duplicates expected
    
    for (int i = 0; i < numElements; i++) {
        int num = dis(gen);
        string element = "custom_element_" + to_string(num);
        AddElement(element);
    }
    
    cout << "Added " << numElements << " elements" << endl;
    GetCardinality();
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printUsage();
        return 0;
    }
    
    string firstArg = argv[1];
    
    if (firstArg == "--help" || firstArg == "-h") {
        printUsage();
        return 0;
    }
    
    if (firstArg == "--demo") {
        runDemo();
        return 0;
    }
    
    if (argc == 3) {
        try {
            int precision = stoi(argv[1]);
            int numElements = stoi(argv[2]);
            
            if (precision < 1 || precision > 16) {
                cout << "Error: Precision must be between 1 and 16" << endl;
                return 1;
            }
            
            if (numElements < 1) {
                cout << "Error: Number of elements must be positive" << endl;
                return 1;
            }
            
            runCustomTest(precision, numElements);
            return 0;
            
        } catch (const exception& e) {
            cout << "Error: Invalid arguments. Use --help for usage information." << endl;
            return 1;
        }
    }
    
    cout << "Error: Invalid number of arguments. Use --help for usage information." << endl;
    return 1;
} 