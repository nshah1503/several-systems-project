//
// Created by Naisheel on 2/17/25.
//

#ifndef WITHOUTMUTEX_H
#define WITHOUTMUTEX_H
#include "bits/stdc++.h"
#include "bits/Timer.h"
#include "config.h"

// extern constexpr size_t DATA_SIZE = 5000000;


class WithoutMutex {
private:
  static void ProcessDataset(span<int> arr, int& sum);
  static std::vector<std::array<int, DATA_SIZE>> GenerateDataset();
  static void Run(std::vector<std::array<int, DATA_SIZE>>& datasets);
public:
  WithoutMutex()
  {
    auto dataset = GenerateDataset();
    Run(dataset);
  }
};



#endif //WITHOUTMUTEX_H
