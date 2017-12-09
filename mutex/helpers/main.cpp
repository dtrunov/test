#include <iostream>
#include <thread>
#include <unistd.h>
#include <fstream>

namespace {
mutex mtx;
rw_mutex rw_mtx;
spinmutex s_mtx;
}

//const int status = pthread_spin_init(&spin_mutex_, PTHREAD_PROCESS_PRIVATE);
//const int status = pthread_spin_destroy(&spin_mutex_);
//const int status = pthread_mutex_init(&th_mutex_, NULL);
//const int status = pthread_mutex_destroy(&th_mutex_);
//const int status = pthread_rwlock_init(&rwlock_, NULL);
//const int status = pthread_rwlock_destroy(&rwlock_);

void thread_main1() {
//  const int status = pthread_spin_lock(&spin_mutex_);
//  const int status = pthread_spin_unlock(&spin_mutex_);
//  const int status = pthread_mutex_lock(&th_mutex_);
//  const int status = pthread_mutex_unlock(&th_mutex_);

  sleep(1000);
}

void thread_main2() {
//  const int status = pthread_spin_lock(&spin_mutex_);
//  const int status = pthread_spin_unlock(&spin_mutex_);
//  const int status = pthread_mutex_lock(&th_mutex_);
//  const int status = pthread_mutex_unlock(&th_mutex_);

  sleep(1000);
}

void thread_main3() {
//const int status = pthread_rwlock_rdlock(&rwlock_);
//const int status = pthread_rwlock_unlock(&rwlock_);
 sleep(1000);
}

void thread_main4() {
  //const int status = pthread_rwlock_rwlock(&rwlock_);
//const int status = pthread_rwlock_unlock(&rwlock_);
  sleep(1000);
}


int main() {
  std::fstream f("/home/box/main.pid", std::ios_base::in | std::ios_base::out | std::ios_base::app);

  if (!(f.is_open())) {
    std::cout << "Failed during open file\n";
    return 1;
  }
  f << getpid();
  f.close();

  std::thread tr1(thread_main1);
  std::thread tr2(thread_main2);
  std::thread tr3(thread_main3);
  std::thread tr4(thread_main4);
  tr1.join();
  tr2.join();
  tr3.join();
  tr4.join();
  return 0;
}