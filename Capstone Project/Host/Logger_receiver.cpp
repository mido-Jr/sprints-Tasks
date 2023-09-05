#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>
#include <chrono>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <string>

#include "../libraries/file.h"

int server_socket; 

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

void setup_ethernet_connection(const std::string& logReceiverIP, int logReceiverPort) {
    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cout << "Socket creation failed";
        // Handle the error or exit as appropriate
        return; // Terminate the function
    }

    // Set up server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(logReceiverPort);
    server_address.sin_addr.s_addr = inet_addr(logReceiverIP.c_str());
    
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        close(server_socket);
        return; // Terminate the function
    }
    
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        return; // Terminate the function
    }
    
    std::cout << "Server is listening for incoming connections..." << std::endl;
}


int main() {

    Configuration config;
    read_configuration("../../config.txt", config);
        
    setup_ethernet_connection(config.logReceiverIP, config.logReceiverPort);



    while (true) {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);

        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket == -1) {
            perror("Accept failed");
            close(server_socket);
            return 1;
        }

        std::cout << "Connected to a client." << std::endl;

        char buffer[1024];
        while (true) {
            int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) {
                break; // Connection closed or error
            }
            buffer[bytes_received] = '\0';
            std::cout << "Received log: " << buffer << std::endl;
        }

        close(client_socket);
        std::cout << "Client disconnected." << std::endl;
    }

    close(server_socket);

    return 0;
}

