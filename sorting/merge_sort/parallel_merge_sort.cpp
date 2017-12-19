#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <memory>

template<typename T>
void mergeResults(T* array_first,
                  uint32_t size_first,
                  T* array_second,
                  uint32_t size_second,
                  std::function<bool(T, T)> comparator);

template <typename T> void mergeSort(T* array, uint32_t size, std::function<bool(T, T)> comparator);

int main() {
#include "data_set.cpp";
  std::function<bool(int, int)> func = [](int first, int second) -> bool {
    return first < second;
  };

  int arr_size = sizeof(arr) / sizeof(int);
  int qty1 = arr_size/2;
  int qty2 = arr_size - qty1;

#pragma omp parallel num_threads(2)
  {
    int i = omp_get_thread_num();
    if (i == 0) { //first thread
      mergeSort(arr, qty1, func);
    } else { //second thread
      mergeSort(arr + qty1, qty2, func);
    }
#pragma omp barrier
}

  mergeResults(arr, qty1, arr + qty1, qty2, func);
  uint32_t previous_element = 0;
  std::cout << "####size = " << arr_size << "\n";
  for (uint32_t i = 0; i < arr_size; ++i) {
    if (previous_element > arr[i]) {
      std::cout << "incorrect sorting result\n";
      std::cout << "previous element = " << previous_element << "\n";
      std::cout << "current element = " << arr[i] << "\n";
      std::cout << "number of element = " << i << "\n\n\n";
      break;
    }
    previous_element = arr[i];
  }
  std::cout << "\n\n\n=====RESULT=====\n\n\n";
std::for_each(arr, arr+ arr_size, [](int el) {
std::cout << el << " ";
});
  return 0;
}

template<typename T>
void mergeResults(T* array_first,
                  uint32_t size_first,
                  T* array_second,
                  uint32_t size_second,
                  std::function<bool(T, T)> comparator) {
  uint32_t result_size = size_first+size_second;
  const uint32_t max_size = (size_first > size_second)?size_first:size_second;
  if (1 == max_size) {
    if (!comparator(array_first[0], array_second[0])) {
      std::swap(array_first[0], array_second[0]);
    }
    return;
  }
  int32_t first_index, second_index, result_index;
  first_index = second_index = result_index = 0;

  std::unique_ptr<T[]> result_array(new T[result_size]);

  for (; result_index < result_size;) {
    if (first_index < size_first && second_index < size_second) {
      if(!comparator(array_first[first_index], array_second[second_index])) {
        result_array[result_index] = array_second[second_index];
        ++second_index;
        ++result_index;
      } else {
        result_array[result_index] = array_first[first_index];
        ++first_index;
        ++result_index;
      }
    } else if (first_index < size_first) {
      result_array[result_index] = array_first[first_index];
      ++first_index;
      ++result_index;
    } else if (second_index < size_second) {
      result_array[result_index] = array_second[second_index];
      ++second_index;
      ++result_index;
    } else {
      std::cout<<"Fatal error\n";
      exit(1);
    }
  }
  std::move(result_array.get(), (result_array.get())+result_size, array_first);
}

template <typename T> void mergeSort(T* array, uint32_t size, std::function<bool(T, T)> comparator){
  if (size == 1) {
    return;
  }
  uint32_t first_part = 0;
  uint32_t second_part = 0;
  first_part = size/2;
  second_part = size-first_part;
  mergeSort(array, first_part, comparator);
  mergeSort(array+first_part, second_part, comparator);
  mergeResults(array, first_part, array+first_part, second_part, comparator);
}

