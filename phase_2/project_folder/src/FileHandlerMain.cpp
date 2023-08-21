#include "FileHandler.h"
#include "NamedPipe.h"
#include "SharedMemory.h"
#include "Logger.h"

int main() {
    // Initialize the logger
    Logger::initialize("run_logs.txt");

    try {
        // Create an instance of the FileHandler class
        FileHandler fileHandler("file_handler_pipe", "file_handler_shared_memory");

        // Start the FileHandler
        fileHandler.start();
    } catch (const std::exception& e) {
        // Log any exceptions
        Logger::log("Exception: " + std::string(e.what()));
    }

    // Clean up the logger
    Logger::shutdown();

    return 0;
}
