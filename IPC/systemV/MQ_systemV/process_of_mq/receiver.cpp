#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

#include "pimpl_mq_sysV.h"

int main() {
  MQPimpl mq("/home/dtrunov/CLionProjects/MQ_systemV/stest", true);
  if (!mq) {
    std::cout << "mq isn't valid\n";
    return 1;
  }
  int fd;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  char *filename = "/home/dtrunov/CLionProjects/MQ_systemV/result";
  fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, mode);
  if (-1 == fd) {
    int error = errno;
    std::cout << "Open file is failed" << strerror(error) << "\n";
    return 1;
  }
  const int BUFF_SIZE = 9000;
  char buff[BUFF_SIZE] = {0};
  ssize_t receive_data = 0, write_data = 0;
  while (true) {
    receive_data = mq.RecvMsg(buff, BUFF_SIZE);
    if (-1 == receive_data) {
      std::cout << "RecvMsg failed " << strerror(errno) << "\n";
      break;
    }
    std::cout << "Receive data = " << receive_data << "\n";
    if (!strcmp(buff, "EOF")) {
      std::cout << "EOF\n";
      break;
    }
    write_data = write(fd, buff, receive_data);
    if (write_data != receive_data) {
      std::cout << "Write data = " << write_data << "receive data = " << receive_data << "\n";
    }
    memset(buff, 0, receive_data);
  }
  close(fd);
}