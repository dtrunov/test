#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory>
#include <signal.h>

bool CreateFIFO(std::string &name_fifo) {
    if (-1 == mkfifo(name_fifo.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) && errno != EEXIST) {
        std::cout<<strerror(errno)<<"\n";
        std::cout << "ERROR:can not create fifo with path=" << name_fifo.c_str() << "\n";
        return false;
    }
    return true;
}

int set_non_block(int fd) {
    int flags;
    if (-1 == (flags = fcntl(fd, F_GETFL, 0))) {
        flags = 0;
    }
    return fcntl(fd, F_SETFL, flags|O_NONBLOCK);
}

class DataTransmitter {
public:
    DataTransmitter(const std::string &name_read_fifo, const std::string& name_write_fifo) : name_read_fifo_(name_read_fifo),
                                                                                name_write_fifo_(name_write_fifo),
                                                                                read_fifo_(-1), write_fifo_(-1) {}

    bool Init() {

        if (!CreateFIFO(name_read_fifo_) || !CreateFIFO(name_write_fifo_)) {
            return false;
        }
        write_fifo_ = open(name_write_fifo_.c_str(), O_WRONLY, 0);
        read_fifo_ = open(name_read_fifo_.c_str(), O_RDWR, 0);
        if (write_fifo_ == -1 || read_fifo_ == -1) {
            std::cout<<strerror(errno)<<"\n";
            std::cout << "ERROR: during open of FIFO\n";
            return false;
        }
        set_non_block(write_fifo_);
        set_non_block(read_fifo_);
        return true;
    }

    ~DataTransmitter() {
        if (write_fifo_ != -1) {
            close(write_fifo_);
        }
        if (read_fifo_ != -1) {
            close(read_fifo_);
        }
        unlink(name_read_fifo_.c_str());
        unlink(name_write_fifo_.c_str());
    }

    void ProcessData() {
        const uint16_t SIZE_BUFF = 512;
        unsigned char buff[SIZE_BUFF] = {0};
        int16_t read_characters = 0;
        fd_set fifo_set;
        int result = 0;
        while (true) {
            FD_ZERO(&fifo_set);
            FD_SET(read_fifo_, &fifo_set);
            result = select(read_fifo_+1, &fifo_set, NULL, NULL, NULL);
            if (0 == result || -1 == result) {
                std::cout<<strerror(errno)<<"\n";
                std::cout<<"select FAILED";
                return;
            }
            if (FD_ISSET(read_fifo_, &fifo_set)) {
                read_characters = read(read_fifo_, buff, SIZE_BUFF);
                if (read_characters == -1) {
                    std::cout<<strerror(errno)<<"\n";
                    std::cout << "ERROR: during read\n";
                    return;
                }
                std::cout<<"Receive buff = "<<buff<<"\n";
                write(write_fifo_, buff, read_characters);
            }
 }
    }


private:
    std::string name_read_fifo_;
    std::string name_write_fifo_;
    int read_fifo_;
    int write_fifo_;
};

std::shared_ptr<DataTransmitter> ptr_dt;

void sig_handler(int signal) {
    if (SIGINT == signal) {
        ptr_dt.reset();
        exit(0);
    }
}

void change_handling_signal() {
    struct sigaction sig_act;
    memset (&sig_act, 0, sizeof(sig_act));
    sig_act.sa_handler = sig_handler;
    sigfillset(&sig_act.sa_mask);
    sigaction(SIGINT, &sig_act, NULL);
}

int main() {
    change_handling_signal();
    std::string write_fifo("/tmp/write.fifo");
    std::string read_fifo("/tmp/read.fifo");
    ptr_dt = std::make_shared<DataTransmitter>(read_fifo, write_fifo);
    if (!ptr_dt->Init()) {
        std::cout<<"Init is failed\n";
        return 0;
    }
    ptr_dt->ProcessData();
    return 0;
}