cmake_minimum_required(VERSION 3.28)
project(MultithreadingConcepts)

set(CMAKE_CXX_STANDARD 23)

add_executable(MultithreadingConcepts main.cpp
        bits/Timer.h
        bits/stdc++.h
        Mutexes.cpp
        Mutexes.h
        WithoutMutex.cpp
        WithoutMutex.h
        config.h)
