#include <iostream>
#include <unistd.h>
#include "sem.h"

int main() {
  sem custom_sem("/tmp/temp.sem", 16);
  if (!custom_sem.isValid()) {
    std::cout<<"custom_serm isn't valid\n";
    return 1;
  }
  sleep(1000);
  return 0;
}