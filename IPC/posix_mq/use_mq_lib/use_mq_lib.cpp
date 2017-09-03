#include "my_mq.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

int main() {
  my_mq mq;
  if (!mq.init()) {
    std::cout << "Program is finishing\n";
    return 1;
  }
  char *buff = new(std::nothrow) char[mq.msgsize()];

  if (buff != NULL) {
    std::cout << "Create buff successfully\n";
  } else {
    std::cout << "We have problem HUSTON\n";
    return 1;
  }
  ssize_t result = -1;

  if ((result = mq.mqreceive(buff, mq.msgsize())) != -1) {
    std::ofstream ofs("message.txt", std::ofstream::out);
    ofs.write(buff, result);
    ofs.close();
  } else {
    std::cout << "Receiving of message is failed\n";
  }
  delete[] buff;
  return 0;
}
