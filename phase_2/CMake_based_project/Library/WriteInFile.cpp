#include "WriteInFile.h"
#include <fstream>

void WriteInFile::write(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}
