#include "SharedMemory.h"
#include <iostream>
#include <cstring>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

SharedMemory::SharedMemory(const std::string& name, size_t size)
        : shmName_(name), shmSize_(size), shmFd_(-1), shmPtr_(nullptr), semaphore_(nullptr) {}

SharedMemory::~SharedMemory() {
    close();
}

bool SharedMemory::create() {
    shmFd_ = shm_open(shmName_.c_str(), O_CREAT | O_RDWR, 0666);
    if (shmFd_ == -1) {
        std::cerr << "Failed to create shared memory segment." << std::endl;
        return false;
    }

    if (ftruncate(shmFd_, shmSize_) == -1) {
        std::cerr << "Failed to set size of shared memory segment." << std::endl;
        close();
        return false;
    }

    shmPtr_ = mmap(nullptr, shmSize_, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd_, 0);
    if (shmPtr_ == MAP_FAILED) {
        std::cerr << "Failed to map shared memory segment into process address space." << std::endl;
        close();
        return false;
    }

    semaphore_ = sem_open("/my_semaphore", O_CREAT, 0666, 0);
    if (semaphore_ == SEM_FAILED) {
        std::cerr << "Failed to create semaphore." << std::endl;
        close();
        return false;
    }

    return true;
}

bool SharedMemory::open() {
    // Implement open logic if needed
    return false;
}

bool SharedMemory::close() {
    if (shmPtr_ != nullptr) {
        munmap(shmPtr_, shmSize_);
        shmPtr_ = nullptr;
    }

    if (shmFd_ != -1) {
        ::close(shmFd_);
        shmFd_ = -1;
    }

    if (semaphore_ != nullptr) {
        sem_close(semaphore_);
        semaphore_ = nullptr;
    }

    return true;
}

bool SharedMemory::write(const void* data, size_t size) {
    // Implement write logic using shmPtr_
    return false;
}

bool SharedMemory::read(void* buffer, size_t size) {
    // Implement read logic using shmPtr_
    return false;
}

void* SharedMemory::getMemoryPointer() {
    return shmPtr_;
}
