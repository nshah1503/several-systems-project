//
// Created by Naisheel on 2/17/25.
//

#ifndef MUTEXES_H
#define MUTEXES_H
#include "bits/stdc++.h"
#include "bits/Timer.h"
#include "config.h"
// extern constexpr size_t DATA_SIZE = 5000000;

class Mutexes {
private:
  static void ProcessDataset(const std::array<int, DATA_SIZE>& arr, int& sum, std::mutex& mtx);
  static void Run();
public:
  Mutexes()
  {
    Run();
  }
};



#endif //MUTEXES_H
