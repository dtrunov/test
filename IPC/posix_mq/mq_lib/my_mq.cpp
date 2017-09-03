#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


#include "my_mq.h"

my_mq::my_mq(std::string name, mq_attr *attr) : name(name),
                                                mq_id(0) {
  (this->attr).mq_flags = attr->mq_flags;
  (this->attr).mq_maxmsg = attr->mq_maxmsg;
  (this->attr).mq_msgsize = attr->mq_msgsize;
  (this->attr).mq_curmsgs = attr->mq_curmsgs;
}

my_mq::my_mq() : name("/test.mq"),
                 mq_id(0) {
  memset(&attr, 0, sizeof(mq_attr));
}

bool my_mq::init() {
  mq_id = mq_open(name.c_str(),
                  O_RDWR | O_CREAT | O_EXCL,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
                  (attr.mq_maxmsg) ? &attr : NULL);
  bool result = false;
  if (-1 == mq_id && EEXIST != errno) {
    strerror(errno);
    std::cout << "I could not create mq\n";
  } else if (EEXIST != errno) {
    std::cout << "mq with name - " << name.c_str() << " already exists\n";
    result = true;
  } else {
    std::cout << "mq has been created successfully\n";
    result = true;
  }
  if (result) {
    mq_getattr(mq_id, &attr);
  }
  return result;
}

my_mq::~my_mq() {
  if (mq_id != -1) {
    mq_close(mq_id);
    mq_unlink(name.c_str());
  }
}

ssize_t my_mq::mqsend(char *buff, uint32_t len) {
  ssize_t result = -1;
  if ((result = mq_send(mq_id, buff, len, 0)) == -1) {
    std::cout << "mq_send error - " << strerror(errno) << "\n";
  } else {
    std::cout << "message was sent successfully\n";
  }
  return result;
}

ssize_t my_mq::mqreceive(char *buff, uint32_t len) {
  ssize_t result = -1;;
  if (len < attr.mq_msgsize) {
    std::cout << "length of buffer is not enough " << len << " < " << attr.mq_msgsize << "\n";
    return result;
  }
  if ((result = mq_receive(mq_id, buff, len, NULL)) == -1) {
    std::cout << "Message was recived successfully \n";
  } else {
    std::cout << "mq_receive error - " << strerror(errno) << "\n";
  }
  return result;
}

long my_mq::flags() {
  return attr.mq_flags;
}

long my_mq::maxmsg() {
  return attr.mq_maxmsg;
}

long my_mq::msgsize() {
  return attr.mq_msgsize;
}

long my_mq::curmsgs() {
  return attr.mq_curmsgs;
}
   
