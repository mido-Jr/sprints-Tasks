#ifndef PROJECT_FOLDER_SHAREDMEMORY_H
#define PROJECT_FOLDER_SHAREDMEMORY_H

#include <string>
#include <cstddef>
#include <semaphore.h>

class SharedMemory {
public:
    SharedMemory(const std::string& name, size_t size);
    ~SharedMemory();

    bool create();
    bool open();
    bool close();

    bool write(const void* data, size_t size);
    bool read(void* buffer, size_t size);

    void* getMemoryPointer();

private:
    std::string shmName_;
    size_t shmSize_;
    int shmFd_;
    void* shmPtr_;
    sem_t* semaphore_;
};

#endif // PROJECT_FOLDER_SHAREDMEMORY_H
