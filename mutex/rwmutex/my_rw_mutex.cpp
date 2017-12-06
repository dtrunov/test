#include "my_rw_mutex.h"
#include "helper.h"

rw_mutex::rw_mutex() {
  const int status = pthread_rwlock_init(&rwlock_, NULL);
  helper::log_status(0 == status, "pthread_rwlock_init", errno);
  helper::assertion(0 == status);
}
rw_mutex::~rw_mutex() {
  const int status = pthread_rwlock_destroy(&rwlock_);
  helper::log_status(0 == status, "pthread_rwlock_destroy", errno);
  helper::assertion(0 == status);
}
void rw_mutex::rd_lock() {
  const int status = pthread_rwlock_rdlock(&rwlock_);
  helper::log_status(0 == status, "pthread_rwlock_rdlock", errno);
  helper::assertion(0 == status);
}
void rw_mutex::wr_lock() {
  const int status = pthread_rwlock_wrlock(&rwlock_);
  helper::log_status(0 == status, "pthread_rwlock_wrlock", errno);
  helper::assertion(0 == status);
}
void rw_mutex::release() {
  const int status = pthread_rwlock_unlock(&rwlock_);
  helper::log_status(0 == status, "pthread_rwlock_unlock", errno);
  helper::assertion(0 == status);
}

bool rw_mutex::try_rd_lock() {
  const int status = pthread_rwlock_tryrdlock(&rwlock_);
  if (-1 == status && EBUSY == errno) {
    return false;
  }
  helper::log_status(0 == status, "pthread_rwlock_tryrdlock", errno);
  helper::assertion(0 == status);
  return true;
}
bool rw_mutex::try_wr_lock() {
  const int status = pthread_rwlock_trywrlock(&rwlock_);
  if (-1 == status && EBUSY == errno) {
    return false;
  }
  helper::log_status(0 == status, "pthread_rwlock_trywrlock", errno);
  helper::assertion(0 == status);
  return true;
}
