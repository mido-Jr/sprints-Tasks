#include "FileHandler.h"
#include "NamedPipe.h"
#include "SharedMemory.h"
#include "Logger.h"

FileHandler::FileHandler(const std::string& pipeName, const std::string& sharedMemoryName)
        : namedPipeName(pipeName), sharedMemory_(sharedMemoryName, sizeof(std::vector<std::string>)) {
    // Create or open the shared memory segment
    sharedMemory_.create();
}

FileHandler::~FileHandler() {
    // The shared memory will be closed and released when its destructor is called
}

void FileHandler::start() {
    try {
        NamedPipe namedPipe(namedPipeName, NamedPipe::Mode::READ);
        Logger::log("File Handler started.");

        while (true) {
            std::string request = namedPipe.read();
            handleRequest(request);
        }
    } catch (const std::exception& ex) {
        Logger::log("File Handler encountered an error: " + std::string(ex.what()));
    }

    Logger::log("File Handler stopped.");
}

void FileHandler::handleRequest(const std::string& request) {
    if (request == "LIST_FILES") {
        sendFileList();
    } else if (request.find("READ_FILE:") == 0) {
        std::string filePath = request.substr(strlen("READ_FILE:"));
        sendFileContent(filePath);
    }
}

void FileHandler::sendFileList() {
    try {
        // Prepare the file list (for demonstration, use a hardcoded list)
        std::vector<std::string> fileList = {"file1.txt", "file2.txt", "file3.txt"};

        // Copy the file list to the shared memory
        sharedMemory_.write(fileList.data(), fileList.size() * sizeof(std::string));

        Logger::log("File list sent to shared memory.");
    } catch (const std::exception& ex) {
        Logger::log("Error sending file list: " + std::string(ex.what()));
    }
}

void FileHandler::sendFileContent(const std::string& filename) {
    try {
        // Open the requested file
        std::ifstream inputFile(filename, std::ios::binary);
        if (!inputFile.is_open()) {
            Logger::log("Failed to open file: " + filename);
            return;
        }

        // Get the size of the file
        inputFile.seekg(0, std::ios::end);
        size_t fileSize = static_cast<size_t>(inputFile.tellg());
        inputFile.seekg(0, std::ios::beg);

        // Allocate memory to read the file content
        char* contentBuffer = new char[fileSize];
        inputFile.read(contentBuffer, fileSize);
        inputFile.close();

        // Write the file content to shared memory
        sharedMemory_.write(contentBuffer, fileSize);

        delete[] contentBuffer;

        Logger::log("File content sent to shared memory.");
    } catch (const std::exception& ex) {
        Logger::log("Error sending file content: " + std::string(ex.what()));
    }
}

