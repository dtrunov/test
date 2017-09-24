//
// Created by dtrunov on 9/10/17.
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "sem.h"

namespace {
void print_error(const char* error, int err) {
  std::cout << error<<"\n Errno: ";
  strerror(err);
  std::cout<<"\n";
}
}

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};

sem::sem(const char *file_name) : isValid_(false),
                                  semNum_(2),
                                  semId_(-1) {
  isValid_ = init(file_name);
}
sem::sem(const char *file_name, const uint8_t sem_num) : isValid_(false),
                                                         semNum_(sem_num),
                                                         semId_(-1) {
  isValid_ = init(file_name);
}

bool sem::init(const char *file_name) {
  key_t id = ftok(file_name, 1);
  if (-1 == id) {
    print_error("Failed during creation of id", errno);
    return false;
  }
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  mode |= IPC_CREAT;
  semId_ = semget(id, semNum_, mode);
  if (-1 ==  semId_) {
    print_error("Failed during semafor creation", errno);
    return false;
  }
  unsigned short* sem_vals = new unsigned short[semNum_];
  for (unsigned short i = 0; i < semNum_; ++i ) {
    sem_vals[i] = i;
  }
  semun arg;
  arg.array = sem_vals;
  if (-1 == semctl(semId_, 0, SETALL, arg)) {
    print_error("Failed during semctl SETALL", errno);
    delete[] sem_vals;
    return false;
  }
  delete[] sem_vals;
  return true;
}

bool sem::isValid() {
  return isValid_;
}

bool sem::check_sem_val(unsigned short *sem_vals, uint8_t sem_num) {
  if (sem_num != semNum_) {
    std::cout<<"Incorrect parameter sem_num\n";
    return false;
  }
  unsigned short* tmp = new unsigned short [semNum_];
  semun arg;
  arg.array = tmp;
  if (-1 == semctl(semId_, 0, GETALL, arg)) {
    print_error("Failed during semctl GETALL", errno);
    delete [] tmp;
    return false;
  }

  bool result = (0 == memcmp(sem_vals, tmp, semNum_*sizeof(unsigned short)))? true : false;;
  delete [] tmp;
  return result;
}

