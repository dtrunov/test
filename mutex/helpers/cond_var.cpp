#include <iostream>
#include <thread>
#include <unistd.h>
#include <fstream>

//const int status = pthread_mutex_init(&th_mutex_, NULL);
//const int status = pthread_mutex_destroy(&th_mutex_);
//const int status = pthread_rwlock_init(&rwlock_, NULL);
//const int status = pthread_rwlock_destroy(&rwlock_);
//bool cond = false;

void thread_main1() {
//  const int status = pthread_mutex_lock(&th_mutex_);
// while(cond) {
// pthread_cond_wait(&th_cond_var, &th_mutex_);
//}
//  const int status = pthread_mutex_unlock(&th_mutex_);
  //pthread_barrier_wait(ptr_data->barier);
  sleep(1000);
}

void thread_main2() {
//const int status = pthread_mutex_lock(&th_mutex_);
//pthread_cond_signal(&th_cond_var);
//  const int status = pthread_mutex_unlock(&th_mutex_);
  //pthread_barrier_wait(ptr_data->barier);
  sleep(1000);
}


int main() {

  //pthread_barrier_t barier
  //status = pthread_barrier_init(&barier, NULL, numCPU+1);

  std::fstream f("/home/box/main.pid", std::ios_base::in | std::ios_base::out | std::ios_base::app);

  if (!(f.is_open())) {
    std::cout << "Failed during open file\n";
    return 1;
  }
  f << getpid();
  f.close();

  std::thread tr1(thread_main1);
  std::thread tr2(thread_main2);
  //pthread_barrier_wait(ptr_data->barier);
  tr1.join();
  tr2.join();
  return 0;
}
