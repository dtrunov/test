//
// Created by dtrunov on 11/11/17.
//
#include <iostream>
#include <assert.h>
#include <string.h>
#include "helper.h"

void helper::assertion(bool expr) {
  assert(expr);
}
void helper::log_status(bool status, const std::string &function_name, int error) {
  if (status) {
    std::cout<< function_name <<" successfull\n";
  } else {
    std::cout << function_name << "failed with error - " << strerror(error) << "\n";
  }
}
