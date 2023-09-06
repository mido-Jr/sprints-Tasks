#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>

class ConfigurationFile {
public:
    ConfigurationFile() {}

    void readFile(const std::string &fileName);
    std::string get(const std::string &key);

private:
    std::map<std::string, std::string> _map;
};

#endif // CONFIGURATIONFILE_H
