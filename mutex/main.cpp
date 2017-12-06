#include <iostream>
#include <thread>
#include <unistd.h>
#include <fstream>
#include "my_mutex.h"
#include "my_rw_mutex.h"
#include "spinmutex.h"
namespace {
mutex mtx;
rw_mutex rw_mtx;
spinmutex s_mtx;
}
void thread_main1() {
  //mtx.lock();
  //s_mtx.spin_lock();
  std::cout<<"\n=======thread_main1 before rd_lock\n";
  rw_mtx.rd_lock();
  std::cout<<"\n=======thread_main1 after rd_lock\n";
  sleep(100);
  rw_mtx.release();
  std::cout<<"\n=======thread_main1 after release\n";
  sleep(1000);
}

void thread_main2() {
  //mtx.lock();
  //s_mtx.spin_lock();

  std::cout<<"\n=======thread_main2 before rd_lock\n";
  rw_mtx.rd_lock();
  std::cout<<"\n=======thread_main2 after rd_lock\n";
  sleep(1000);
}


int main() {
//  std::fstream f("/home/box/main.pid", std::ios_base::in | std::ios_base::out | std::ios_base::app);
//
//  if (!(f.is_open())) {
//    std::cout << "Failed during open file\n";
//    return 1;
//  }
//  f << getpid();
//  f.close();

  std::thread tr1(thread_main1);
  std::thread tr2(thread_main2);
  tr1.join();
  tr2.join();
  return 0;
}