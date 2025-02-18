//
// Created by Naisheel on 2/17/25.
//

#include "WithoutMutex.h"

void WithoutMutex::ProcessDataset(const span<int> arr, int& sum)
{
  for (const auto x: arr)
  {
    constexpr auto limit = static_cast<double>(std::numeric_limits<int>::max());
    const auto y = static_cast<double>(x/limit);
    sum += static_cast<int>(std::sin(std::cos(y))*limit);
  }
}

std::vector<std::array<int, DATA_SIZE>> WithoutMutex::GenerateDataset()
{
  Timer T("Generating Dataset");
  std::minstd_rand rne; // check out LCG- linear congruential engine algorithm
  std::vector<std::array<int, DATA_SIZE>> datasets{4};
  for (auto& arr: datasets)
  {
    std::ranges::generate(arr, rne);
  }
  return datasets;
}

void WithoutMutex::Run(std::vector<std::array<int, DATA_SIZE>>& datasets)
{
  Timer T("All processes without mutex");
  std::vector<std::thread> workers;
  struct value
  {
    int v;
    char padding[60];
  };
  std::array<value, 4>sum = {0,0,0,0};
  for(size_t i = 0; i < 4; ++i)
  {
    workers.push_back(std::thread{ ProcessDataset, std::span{ datasets[i] }, std::ref(sum[i].v) });
  }

  for (auto& worker: workers)
  {
    worker.join();
  }

  // std::cout << "Sum is: " << std::accumulate(sum.begin(), sum.end(), 0) << std::endl;
  std::cout << "Sum is: " << std::accumulate(sum.begin(), sum.end(), 0,
    [](const int acc, const value& val) {
        return acc + val.v;
    }) << std::endl;
}