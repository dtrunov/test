//
// Created by dtrunov on 8/4/17.
//

#ifndef MQ_SYSTEMV_MQ_SYSV_H
#define MQ_SYSTEMV_MQ_SYSV_H

class MQ_SYSV {
 public:
  MQ_SYSV(const char *path, bool auto_destroy);
  ssize_t SendMsg(void *buff, size_t length);
  ssize_t RecvMsg(void *buff, size_t length);
  operator bool();
  void FreeResources();
  ~MQ_SYSV();
 private:
  const int MAX_MQ_MSG;
  int mq_id_;
  bool is_auto_destroy_;
};

#endif //MQ_SYSTEMV_MQ_SYSV_H
