#ifndef PROJECT_FOLDER_FILEHANDLER_H
#define PROJECT_FOLDER_FILEHANDLER_H
#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include "SharedMemory.h"
#include "Logger.h"

class FileHandler {
public:
    FileHandler(const std::string& pipeName, const std::string& sharedMemoryName);
    ~FileHandler();

    void start(); // Start listening for requests

private:
    void handleRequest(const std::string& request);

    void sendFileList();
    void sendFileContent(const std::string& filePath);

    SharedMemory sharedMemory_; // Shared memory instance

    std::string namedPipeName;   // Named pipe name for communication
};

#endif // PROJECT_FOLDER_FILEHANDLER_H
