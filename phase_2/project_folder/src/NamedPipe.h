#ifndef PROJECT_FOLDER_NAMEDPIPE_H
#define PROJECT_FOLDER_NAMEDPIPE_H
#pragma once

#include <string>
#include <semaphore.h> // Include semaphore.h

class NamedPipe {
public:
    NamedPipe(const std::string& pipeName, bool forReading = false);
    ~NamedPipe();

    bool create();
    bool open();
    void close();

    bool write(const void* data, size_t size);
    bool read(void* buffer, size_t size);

private:
    std::string pipeName_;
    int pipeFd_;
    bool isOpen_;

    sem_t* semaphore_; // Add a semaphore member
};

#endif //PROJECT_FOLDER_NAMEDPIPE_H
