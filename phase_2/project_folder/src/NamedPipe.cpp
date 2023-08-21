#include "NamedPipe.h"
#include <iostream>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

NamedPipe::NamedPipe(const std::string& pipeName, bool forReading)
        : pipeName_(pipeName), pipeFd_(-1), isOpen_(false), semaphore_(nullptr) {

    create();  // Create the named pipe when the instance is created
    if (forReading) {
        // Initialize semaphore for reading end
        semaphore_ = sem_open((pipeName + "_sem").c_str(), O_CREAT, 0666, 1);
        if (semaphore_ == SEM_FAILED) {
            std::cerr << "Failed to initialize semaphore: " << strerror(errno) << std::endl;
            close();
        }
    }
}

NamedPipe::~NamedPipe() {
    close();
    if (semaphore_ != nullptr) {
        sem_close(semaphore_);
        sem_unlink((pipeName_ + "_sem").c_str());
    }
}

bool NamedPipe::create() {
    if (mkfifo(pipeName_.c_str(), 0666) == 0) {
        return true;
    } else {
        std::cerr << "Failed to create named pipe: " << strerror(errno) << std::endl;
        return false;
    }
}

bool NamedPipe::open() {
    pipeFd_ = ::open(pipeName_.c_str(), O_RDWR);
    if (pipeFd_ >= 0) {
        isOpen_ = true;
        return true;
    } else {
        std::cerr << "Failed to open named pipe: " << strerror(errno) << std::endl;
        return false;
    }
}

void NamedPipe::close() {
    if (isOpen_) {
        ::close(pipeFd_);
        isOpen_ = false;
    }
}

bool NamedPipe::write(const void* data, size_t size) {
    if (isOpen_) {
        ssize_t bytesWritten = ::write(pipeFd_, data, size);
        if (bytesWritten == static_cast<ssize_t>(size)) {
            return true;
        } else {
            std::cerr << "Failed to write to named pipe: " << strerror(errno) << std::endl;
            return false;
        }
    } else {
        std::cerr << "Named pipe is not open for writing." << std::endl;
        return false;
    }
}

bool NamedPipe::read(void* buffer, size_t size) {
    if (isOpen_) {
        if (semaphore_) {
            if (sem_wait(semaphore_) != 0) {
                std::cerr << "Failed to wait on semaphore: " << strerror(errno) << std::endl;
                return false;
            }
        }

        ssize_t bytesRead = ::read(pipeFd_, buffer, size);
        if (bytesRead >= 0) {
            if (semaphore_) {
                sem_post(semaphore_);
            }
            return true;
        } else {
            std::cerr << "Failed to read from named pipe: " << strerror(errno) << std::endl;
            return false;
        }
    } else {
        std::cerr << "Named pipe is not open." << std::endl;
        return false;
    }
}
