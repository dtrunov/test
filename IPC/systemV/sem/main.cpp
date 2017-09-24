#include <iostream>
#include <unistd.h>
#include "sem.h"

int main() {
  unsigned short arr[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  sem custom_sem("/tmp/sem.temp", 16);
  if (!custom_sem.isValid()) {
    std::cout<<"custom_serm isn't valid\n";
    return 1;
  }
  std::cout<<"check validity = "<<custom_sem.check_sem_val(arr, 16)<<"\n";
  return 0;
}