#include "file.h"

void ConfigurationFile::readFile(const std::string &fileName) {
    // Open the file
    std::ifstream file(fileName);

    // Read the file line by line
    for (std::string line; std::getline(file, line);) {
        // Split the line into key and value
        std::string key, value;
        std::stringstream ss(line);
        ss >> key >> value;

        // Store the key and value in the map
        _map[key] = value;
    }

    // Close the file
    file.close();
}

std::string ConfigurationFile::get(const std::string &key) {
    return _map[key];
}
