//
// Created by dtrunov on 8/4/17.
//
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <sys/stat.h>



#include "mq_sysV.h"

MQ_SYSV::MQ_SYSV(const char *path, bool auto_destroy) : mq_id_(-1), MAX_MQ_MSG(8192),
is_auto_destroy_(auto_destroy){
  key_t key = ftok(path, 1);
  if (key != -1) {
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    mq_id_ = msgget(key, IPC_CREAT|mode);
  }
}

MQ_SYSV::operator bool() {
  return mq_id_ != -1;
}

void MQ_SYSV::FreeResources() {
  msgctl(mq_id_, IPC_RMID, NULL);
}

MQ_SYSV::~MQ_SYSV() {
  if (*this && is_auto_destroy_) {
    FreeResources();
  }
}
ssize_t MQ_SYSV::SendMsg(void *buff, size_t length) {
  if (!(*this)) {
    std::cout<<"MQ_SYSV is not valid\n";
    return -1;
  }
  int result  = 0;
  int offset = 0;
  size_t msgsz = 0;
  while (length > offset) {
    if (length - offset <= MAX_MQ_MSG) {
      msgsz = length - offset;
    } else {
      msgsz = MAX_MQ_MSG;
    }

    msgbuf *msg = static_cast<msgbuf*>(alloca(sizeof(long) + msgsz));
    msg->mtype = 1;
    memcpy(&((*msg).mtext), (static_cast<uint8_t*>(buff))+offset, msgsz);
    result = msgsnd(mq_id_, msg, msgsz, 0);
    if (-1 == result) {
      std::cout<<"msgsnd was failed errno = "<<strerror(errno);
      return -1;
    }
    offset += msgsz;
  }
  return offset;
}

ssize_t MQ_SYSV::RecvMsg(void *buff, size_t length) {
  msgbuf *msg = static_cast<msgbuf*>(alloca(sizeof(long) + length));
  msg->mtype = 0;
  ssize_t result = msgrcv(mq_id_, msg, length, 0, MSG_NOERROR);
  if (-1 != result) {
    memcpy(buff, &((*msg).mtext), result);
  }
  return result;
}
