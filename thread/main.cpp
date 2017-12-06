#include <iostream>
#include <thread>
#include <unistd.h>
#include <fstream>

void *thread_main() {
  int i = 0;
  while (i < 100) {
    sleep(1);
    ++i;
  }
}

int main() {
  std::fstream f("/home/box/main.pid", std::ios_base::in | std::ios_base::out | std::ios_base::app);


  if (!(f.is_open())) {
    std::cout << "Failed during open file\n";
    return 1;
  }
  f<< getpid();
  f.close();

  std::thread tr1(thread_main);
  tr1.join();
  return 0;
}