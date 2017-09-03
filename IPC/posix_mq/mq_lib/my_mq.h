#ifndef MY_MQ_H
#define MY_MQ_H
#include <string>
#include <stdlib.h>
#include <mqueue.h>
#include <stdint.h>

class my_mq {
 public:
  my_mq(std::string name, mq_attr *attr);
  my_mq();
  ~my_mq();
  ssize_t mqsend(char *buff, uint32_t len);
  ssize_t mqreceive(char *buff, uint32_t len);
  long flags();
  long maxmsg();
  long msgsize();
  long curmsgs();
  bool init();
 private:
  std::string name;
  mqd_t mq_id;
  mq_attr attr;
};
#endif // MY_MQ_H


