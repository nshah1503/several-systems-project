//
// Created by Naisheel on 2/7/25.
//

#include "Mutexes.h"


void Mutexes::ProcessDataset(const std::array<int, DATA_SIZE>& arr, int& sum, std::mutex& mtx)
{
  for (const auto x: arr)
  {
    // mtx.lock();
    std::lock_guard g{mtx}; // calls lock and automatically unlocks when destroyed RAII
    constexpr auto limit = static_cast<double>(std::numeric_limits<int>::max());
    const auto y = static_cast<double>(x/limit);
    sum += static_cast<int>(std::sin(std::cos(y))*limit);
    // mtx.unlock();
  }
}

void Mutexes::Run()
{
  Timer T;
  std::minstd_rand rne; // check out LCG- linear congruential engine algorithm
  std::vector<std::array<int, DATA_SIZE>> datasets{4};
  std::vector<std::thread> workers;

  for (auto& arr: datasets)
  {
    std::ranges::generate(arr, rne);
  }

  std::mutex mtx;
  int sum = 0;
  for(auto& arr: datasets)
  {
    workers.push_back(std::thread{ ProcessDataset, std::ref(arr), std::ref(sum), std::ref(mtx) });
  }

  for (auto& worker: workers)
  {
    worker.join();
  }

  std::cout << "Sum is: " << sum << std::endl;
}


/*
 Threads with mutex ka funda is this:
 -> locks on all updates
 -> join function for consistently available
 -> unlock it for other threads to access
 -> ts does cause overhead tho
*/