//
// Created by Naisheel on 2/17/25.
//

#ifndef TIMER_H
#define TIMER_H
#include "stdc++.h"


struct Timer {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  std::chrono::duration<float> duration;
  std::string processName;
  Timer(const std::string& process)
  {
    processName = process;
    start = std::chrono::high_resolution_clock::now();
  }
  ~Timer()
  {
    end = std::chrono::high_resolution_clock::now();
    duration = end-start;
    const float ms = duration.count()*100;
    std::cout << "Process name: " << processName << std::endl;
    std::cout << "The process took: " << ms << "ms" << std::endl;
  }
};



#endif //TIMER_H
