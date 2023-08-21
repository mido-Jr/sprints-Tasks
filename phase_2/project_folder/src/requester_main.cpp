#include "Requester.h"

int main() {
    const std::string pipeName = "file_handler_pipe";
    const std::string shmName = "file_handler_shared_memory";

    Requester requester(pipeName, shmName);

    if (!requester.connectToPipe()) {
        return 1;
    }

    std::string directory = "/path/to/directory"; // Replace with the actual directory path
    if (!requester.requestFileList(directory)) {
        return 1;
    }

    requester.receiveFileList();

    std::string filePath = "/path/to/file"; // Replace with the actual file path
    if (!requester.requestFileContent(filePath)) {
        return 1;
    }

    requester.receiveFileContent();

    return 0;
}
