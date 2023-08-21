#ifndef PROJECT_FOLDER_REQUESTER_H
#define PROJECT_FOLDER_REQUESTER_H
#pragma once

#include "NamedPipe.h"
#include "SharedMemory.h"
#include "Logger.h"
#include <string>
#include <vector>

class Requester {
public:
    Requester(const std::string& pipeName, const std::string& shmName);
    ~Requester();

    bool connectToPipe();
    bool requestFileList(const std::string& directory);
    bool requestFileContent(const std::string& filePath);
    void receiveFileList();
    void receiveFileContent();

private:
    NamedPipe namedPipe_;
    SharedMemory sharedMemory_;
    Logger logger_;

    void logAndPrint(const std::string& message);
};

#endif // PROJECT_FOLDER_REQUESTER_H
