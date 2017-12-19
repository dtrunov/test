cmake_minimum_required(VERSION 3.5)
project(merge_sort)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -fopenmp)

set(SOURCE_FILES main.cpp)
add_executable(merge_sort ${SOURCE_FILES})
add_executable(ParallelMergeSort parallel_merge_sort.cpp)