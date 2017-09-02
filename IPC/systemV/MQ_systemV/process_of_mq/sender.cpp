#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

#include "pimpl_mq_sysV.h"

int main() {
  MQPimpl mq("/home/dtrunov/CLionProjects/MQ_systemV/stest", false);
  if (!mq) {
    std::cout << "mq isn't valid\n";
    return 1;
  }
  int fd;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  char *filename = "/home/dtrunov/CLionProjects/MQ_systemV/stest";
  fd = open(filename, O_RDWR | O_CREAT, mode);
  if (-1 == fd) {
    int error = errno;
    std::cout << "Open file is failed" << strerror(error) << "\n";
    return 1;
  }
  const int BUFF_SIZE = 9000;
  char buff[BUFF_SIZE] = {0};
  ssize_t read_data = 0, write_data = 0;
  bool eof = false;
  while (!eof) {
    read_data = read(fd, buff, BUFF_SIZE);
    if (-1 == read_data) {
      std::cout << "Problem during reading of file:" << strerror(errno) << "\n";
      break;
    }
    if (0 == read_data) {
      std::cout << "End of file\n";
      read_data = strlen("EOF")+1;
      strcpy(buff, "EOF");
      eof = true;
    }
    write_data = mq.SendMsg(buff, read_data);
    if (-1 == write_data) {
      return 1;
    }
    if (write_data != read_data) {
      std::cout<<"Write data = "<<write_data<<" Read data = "<<read_data<<"\n";
    }
    memset(buff, 0, read_data);
  }
  close(fd);
  return 0;
}