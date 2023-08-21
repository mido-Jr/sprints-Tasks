#include "Requester.h"

Requester::Requester(const std::string& pipeName, const std::string& shmName)
        : namedPipe_(pipeName), sharedMemory_(shmName, sizeof(FileListData)), logger_("requester_run_logs.txt") {}

Requester::~Requester() {
    namedPipe_.close();
    sharedMemory_.close();
}

bool Requester::connectToPipe() {
    if (!namedPipe_.openForWriting()) {
        logAndPrint("Failed to connect to named pipe.");
        return false;
    }
    logAndPrint("Connected to named pipe.");
    return true;
}

bool Requester::requestFileList(const std::string& directory) {
    if (!namedPipe_.isOpened()) {
        logAndPrint("Named pipe is not opened.");
        return false;
    }

    if (!namedPipe_.write(directory)) {
        logAndPrint("Failed to send directory path through named pipe.");
        return false;
    }

    logAndPrint("Requested file list for directory: " + directory);
    return true;
}

bool Requester::requestFileContent(const std::string& filePath) {
    if (!namedPipe_.isOpened()) {
        logAndPrint("Named pipe is not opened.");
        return false;
    }

    if (!namedPipe_.write(filePath)) {
        logAndPrint("Failed to send file path through named pipe.");
        return false;
    }

    logAndPrint("Requested file content for file: " + filePath);
    return true;
}

void Requester::receiveFileList() {
    try {
        std::vector<std::string> fileList;
        fileList.resize(3);  // Assuming a fixed number of files for demonstration

        if (sharedMemory_.read(fileList.data(), fileList.size() * sizeof(std::string))) {
            logAndPrint("Received file list:");
            for (const std::string& file : fileList) {
                logAndPrint(" - " + file);
            }
        } else {
            logAndPrint("Failed to read file list from shared memory.");
        }
    } catch (const std::exception& ex) {
        logAndPrint("Error receiving file list: " + std::string(ex.what()));
    }
}

void Requester::receiveFileContent() {
    try {
        // Determine the file size from the shared memory size
        size_t fileSize = sharedMemory_.getSize();

        // Allocate memory to receive file content
        char* contentBuffer = new char[fileSize];

        if (sharedMemory_.read(contentBuffer, fileSize)) {
            logAndPrint("Received file content:\n" + std::string(contentBuffer, fileSize));
        } else {
            logAndPrint("Failed to read file content from shared memory.");
        }

        delete[] contentBuffer;
    } catch (const std::exception& ex) {
        logAndPrint("Error receiving file content: " + std::string(ex.what()));
    }
}

void Requester::logAndPrint(const std::string& message) {
    logger_.log(message);
    std::cout << message << std::endl;
}
