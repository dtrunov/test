//
// Created by dtrunov on 8/4/17.
//
#include "pimpl_mq_sysV.h"
#include "mq_sysV.h"

MQPimpl::MQPimpl(const char *path, bool auto_destroy) {
  mq_pimpl = std::make_shared<MQ_SYSV>(path, auto_destroy);
}
ssize_t MQPimpl::SendMsg(void *buff, size_t length) {
  return mq_pimpl->SendMsg(buff, length);
}
ssize_t MQPimpl::RecvMsg(void *buff, size_t length) {
  return mq_pimpl->RecvMsg(buff, length);
}
MQPimpl::operator bool() {
  return mq_pimpl->operator bool();
}
