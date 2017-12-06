#ifndef MUTEX_SPINMUTEX_H
#define MUTEX_SPINMUTEX_H
#include <pthread.h>
class spinmutex {
 public:
  spinmutex();
  ~spinmutex();
  void spin_lock();
  void spin_release();
  bool spin_try_lock();
  spinmutex(const spinmutex&) = delete;
  spinmutex&operator=(const spinmutex&) = delete;
 private:
  pthread_spinlock_t spin_mutex_;
};

#endif //MUTEX_SPINMUTEX_H