//
// Created by dtrunov on 11/11/17.
//

#ifndef MUTEX_HELPERS_H
#define MUTEX_HELPERS_H
#include <string>

class helper {
 public:
  static void assertion(bool expr);
  static void log_status(bool status, const std::string &function_name, int error);
};

#endif //MUTEX_HELPERS_H
