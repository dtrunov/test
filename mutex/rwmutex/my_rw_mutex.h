//
// Created by dtrunov on 11/13/17.
//

#ifndef MUTEX_RW_MUTEX_H
#define MUTEX_RW_MUTEX_H

#include <pthread.h>

class rw_mutex {
 public:
  rw_mutex();
  ~rw_mutex();
  void rd_lock();
  void wr_lock();
  void release();
  bool try_rd_lock();
  bool try_wr_lock();
  rw_mutex(const rw_mutex &) = delete;
  rw_mutex &operator=(const rw_mutex &) = delete;

 private:
  pthread_rwlock_t rwlock_;
};

#endif //MUTEX_RW_MUTEX_H