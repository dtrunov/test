//
// Created by dtrunov on 10/1/17.
//
#include <errno.h>
#include <iostream>
#include <string.h>

#include "my_mutex.h"
#include "helper.h"
mutex::mutex() {
  const int status = pthread_mutex_init(&th_mutex_, NULL);
  helper::log_status(0 == status, "pthread_mutex_init", errno);
  helper::assertion(0 == status);
}

mutex::~mutex() {
  const int status = pthread_mutex_destroy(&th_mutex_);
  helper::log_status(0 == status, "pthread_mutex_destroy", errno);
  helper::assertion(0 == status);
}

void mutex::lock() {
  const int status = pthread_mutex_lock(&th_mutex_);
  helper::log_status(0 == status, "pthread_mutex_lock", errno);
  helper::assertion(0 == status);
}

void mutex::release() {
  const int status = pthread_mutex_unlock(&th_mutex_);
  helper::log_status(0 == status, "pthread_mutex_unlock", errno);
  helper::assertion(0 == status);
}
bool mutex::try_lock() {
  const int status = pthread_mutex_trylock(&th_mutex_);
  if (-1 == status && EBUSY == errno) {
    return false;
  }
  helper::log_status(0 == status, "pthread_mutex_trylock", errno);
  helper::assertion(0 == status);
  return true;
}


