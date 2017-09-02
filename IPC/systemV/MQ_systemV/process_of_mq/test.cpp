//
// Created by dtrunov on 9/2/17.
//

#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <fstream>

#include "pimpl_mq_sysV.h"

int main() {
  MQPimpl mq("/tmp/msg.temp", true);
  if (!mq) {
    std::cout << "mq isn't valid\n";
    return 1;
  }

  std::ofstream ofs ("test.txt", std::ofstream::out);

  const int BUFF_SIZE = 9000;
  char buff[BUFF_SIZE] = {0};
  ssize_t receive_data = 0, write_data = 0;
  receive_data = mq.RecvMsg(buff, BUFF_SIZE);
  if (-1 == receive_data) {
    std::cout << "RecvMsg failed " << strerror(errno) << "\n";
    return 1;
  }
  std::cout << "Receive data = " << receive_data << "\n";
  ofs.write(buff, receive_data);
  ofs.close();
}

