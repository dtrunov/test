//
// Created by dtrunov on 10/1/17.
//

#ifndef MUTEX_MUTEX_H
#define MUTEX_MUTEX_H
#include <pthread.h>

class mutex {
 public:
  mutex();
  ~mutex();
  void lock();
  void release();
  bool try_lock();
  mutex(const mutex&) = delete;
  mutex&operator=(const mutex&) = delete;
 private:
  pthread_mutex_t th_mutex_;

};

#endif //MUTEX_MUTEX_H
