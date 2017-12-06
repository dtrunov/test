#include "spinmutex.h"
#include "helper.h"

spinmutex::spinmutex() {
  const int status = pthread_spin_init(&spin_mutex_, PTHREAD_PROCESS_PRIVATE);
  helper::log_status(0 == status, "pthread_spin_init", errno);
  helper::assertion(0 == status);
}
spinmutex::~spinmutex() {
  const int status = pthread_spin_destroy(&spin_mutex_);
  helper::log_status(0 == status, "pthread_spin_destroy", errno);
  helper::assertion(0 == status);
}
void spinmutex::spin_lock() {
  const int status = pthread_spin_lock(&spin_mutex_);
  helper::log_status(0 == status, "pthread_spin_lock", errno);
  helper::assertion(0 == status);
}

void spinmutex::spin_release() {
  const int status = pthread_spin_unlock(&spin_mutex_);
  helper::log_status(0 == status, "pthread_spin_unlock", errno);
  helper::assertion(0 == status);
}

bool spinmutex::spin_try_lock() {
  const int status = pthread_spin_trylock(&spin_mutex_);
  if (-1 == status && EBUSY == errno) {
    return false;
  }
  helper::log_status(0 == status, "pthread_spin_trylock", errno);
  helper::assertion(0 == status);
  return true;
}