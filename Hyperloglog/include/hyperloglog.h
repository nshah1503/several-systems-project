#pragma once

#include <cstdint>
#include <vector>
#include <string>

using namespace std;
#define hash_t uint64_t

void Hyperloglog(int initial_bit);
void GetCardinality();
void AddElement(const string& element);
void ComputeCardinality();

// add as per requirements
void ComputeBinary(uint64_t hash);
void PositionOfLeftMostOne(uint64_t hash, int& position);

// calculating hash value
void CalculateHash(const string& element, hash_t& hash_value);