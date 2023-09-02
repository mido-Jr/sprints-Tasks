#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include "../libraries/ipc_library.h"
#include "../libraries/logger.h"
#include "../libraries/file.h"


struct Configuration {
    std::string logFilePath;
    std::string MessageQueue;
    std::string logReceiverIP;
    int logReceiverPort;
};

void read_configuration(const std::string& config_file, Configuration& config) {

    ConfigurationFile configFile;
    configFile.readFile(config_file);

    config.logFilePath = configFile.get("logFilePath");
    config.MessageQueue = configFile.get("MessageQueue");
    config.logReceiverIP = configFile.get("logReceiverIP");
    config.logReceiverPort = std::stoi(configFile.get("logReceiverPort"));
}

double performOperation(const std::string& operation, const std::vector<double>& operands) {
    if (operation == "add") {
        double sum = 0;
        for (double operand : operands) {
            sum += operand;
        }
        return sum;
    } else if (operation == "sub") {
        double result = operands[0];
        for (size_t i = 1; i < operands.size(); ++i) {
            result -= operands[i];
        }
        return result;
    } else if (operation == "mul") {
        double result = 1;
        for (double operand : operands) {
            result *= operand;
        }
        return result;
    } else if (operation == "div") {
        if (operands[1] != 0) {
            return operands[0] / operands[1];
        } else {
            std::cerr << "Hint!: Division by zero" << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Hint!: Unsupported operation" << std::endl;
        exit(1);
    }
}

void printHelp(const char* programName) {
    std::cout << "Usage: " << programName << " <operation> <operands...>" << std::endl;
    std::cout << "Supported operations: add, sub, mul, div" << std::endl;
}

void logToDaemon(const std::string& logMessage, Configuration& config) {
    IPCMessageSender sender(config.MessageQueue.c_str());

    try {
        sender.sendMessage(logMessage);
        sender.logMessage("Message sent to log daemon successfully!");
    } catch (const IPCError& error) {
        std::cerr << "Error: " << error.getErrorMessage() << std::endl;
    }
}

int main(int argc, char* argv[]) {

    Configuration config;
    read_configuration("../../config.txt", config);

    if (argc <= 1) {
    	std::cerr << "Hint!: No arguments" << std::endl;
        printHelp(argv[0]);
        return 0;
    }

    if (std::strcmp(argv[1], "--help") == 0) {
    	std::cerr << "Help: How to use !" << std::endl;
        printHelp(argv[0]);
        return 0;
    }

    if (argc <= 2) {
        std::cerr << "Hint!: Insufficient arguments" << std::endl;
        printHelp(argv[0]);
        return 0;
    }

    std::string operation = argv[1]; 
    std::vector<double> operands;
    for (int i = 2; i < argc; ++i) {
        operands.push_back(std::stod(argv[i]));
    }

    double result = performOperation(operation, operands);

    // Log the operation and result
    std::string logMessage = "Operation: " + operation + " ";
    for (double operand : operands) {
        logMessage += std::to_string(operand) + " ";
    }
    
    logMessage += "= " + std::to_string(result);
    logToDaemon(logMessage, config);

    return 0;
}
