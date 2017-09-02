//
// Created by dtrunov on 8/4/17.
//

#ifndef MQ_SYSTEMV_PIMPL_MQ_SYSV_H
#define MQ_SYSTEMV_PIMPL_MQ_SYSV_H
#include <stdio.h>
#include <memory>
class MQ_SYSV;
class MQPimpl {
 public:
  MQPimpl(const char *path, bool auto_destroy);
  ssize_t SendMsg(void *buff, size_t length);
  ssize_t RecvMsg(void *buff, size_t length);
  operator bool();
 private:
  std::shared_ptr<MQ_SYSV> mq_pimpl;
};


#endif //MQ_SYSTEMV_PIMPL_MQ_SYSV_H
