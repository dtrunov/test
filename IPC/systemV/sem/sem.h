//
// Created by dtrunov on 9/10/17.
//

#ifndef SEM_SEM_H
#define SEM_SEM_H

#include <cstdint>
class sem {
 public:
  sem(const char *file_name);
  sem(const char *file_name, const uint8_t sem_num);
  bool isValid();
  bool check_sem_val(unsigned short* sem_vals, uint8_t sem_num);

 private:
  bool isValid_;
  uint8_t semNum_;
  int32_t semId_;

  bool init(const char *file_name);
};

#endif //SEM_SEM_H