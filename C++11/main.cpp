#include <iostream>
#include <future>
#include <unistd.h>
#include <functional>

class test {
 public:
  int foo() {
    for (int i = 0; i < 20; ++i) {
      std::cout << "i = " << i << "\n";
      sleep(1);
    }
    return 20;
  }
};
int main() {
  test obj_test;
//  std::future<int> ft = std::async([]() {
//    for (int i = 0; i < 20; ++i) {
//      std::cout << "i = " << i << "\n";
//      sleep(1);
//    }
//    return 20;
//  });
  //std::future<int> ft = std::async(&test::foo, &obj_test);
  std::future<int> ft = std::async(std::bind(&test::foo, &obj_test));
  std::cout << "ft.get() = " << ft.get();
  return 0;
}

// information about functors bind and fn_mem https://stackoverflow.com/questions/9713477/how-passing-arguments-using-stdmem-fun