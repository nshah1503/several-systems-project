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
  static void ProcessDataset(const std::array<int, DATA_SIZE>& arr, int& sum);
  static void Run();
public:
  WithoutMutex()
  {
    Run();
  }
};



#endif //WITHOUTMUTEX_H
