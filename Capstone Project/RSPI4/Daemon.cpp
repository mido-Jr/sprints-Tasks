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


#include "../libraries/ipc_library.h"
#include "../libraries/logger.h"
#include "../libraries/file.h"



int client_socket;
static volatile sig_atomic_t signal_received = 0;
const int MAX_LOG_SIZE = 1024; // Max size in bytes


struct Configuration {
    std::string logFilePath;
    std::string MessageQueue;
    std::string logReceiverIP;
    std::string DaemonFlag;
    int logReceiverPort;
};

void read_configuration(const std::string& config_file, Configuration& config) {

    ConfigurationFile configFile;
    configFile.readFile(config_file);

    config.logFilePath = configFile.get("logFilePath");
    config.MessageQueue = configFile.get("MessageQueue");
    config.logReceiverIP = configFile.get("logReceiverIP");
    config.DaemonFlag = configFile.get("DaemonFlag");
    config.logReceiverPort = std::stoi(configFile.get("logReceiverPort"));
}

static void handle_signals(int signum) {
    signal_received = signum;
    std::cout<<"Daemon App Stoped !"<<std::endl;
    
}

static void setup_signal_handlers() {
    signal(SIGCHLD, SIG_IGN);   // Ignore child signals
    signal(SIGHUP, SIG_IGN);    // Ignore hangup signals
    signal(SIGTERM, handle_signals);  // Handle termination signal
}

static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);
    
    std::cout<<"Daemon App Started !"<<std::endl;
}


void setup_boost_logger(const std::string& logFilePath) {

    //SetLogFile(logFilePath);
    logger::construct_logger();
}

void setup_ethernet_connection(const std::string& logReceiverIP, int logReceiverPort) {
    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        LOG_ERROR << "Socket creation failed";
        // Handle the error or exit as appropriate
    }

    // Set up server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(logReceiverPort);
    server_address.sin_addr.s_addr = inet_addr(logReceiverIP.c_str());
    
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        LOG_ERROR << "Connect failed"<< " IP address: " << logReceiverIP << " Port: " << logReceiverPort;
        close(client_socket);
        // Handle the error or exit as appropriate
    }

    //std::cout << "setup_ethernet_connection " <<std::endl;
}

void send_log_to_ethernet(const std::string &log) {
    // Send the log message over Ethernet to the external logger collector
    ssize_t sent_bytes = send(client_socket, log.c_str(), log.size(), 0);
    if (sent_bytes == -1) {
        perror("Send failed");
        // Handle the error or exit as appropriate
    }
}

void rotate_log_file(const std::string& logFilePath, Configuration& config) {
    static int file_count = 1;

    std::ostringstream new_log_file_path;
    auto now = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
    new_log_file_path << "logs_" << timestamp << "_" << file_count << ".log";

    if (rename(logFilePath.c_str(), new_log_file_path.str().c_str()) == 0) {

        config.logFilePath = new_log_file_path.str();
        setup_boost_logger(config.logFilePath);
        LOG_WARNING << "Rotated log file: " << new_log_file_path.str() << std::endl;
        
    } else {
        std::cerr << "Failed to rotate log file" << std::endl;
    }
}

int main() {

    // Read the configuration file, extract values, and set up the logger and Ethernet connection

    Configuration config;
    read_configuration("../../config.txt", config);
    
    
    if (config.DaemonFlag == "True"){
    
	skeleton_daemon();
	//setup_signal_handlers();
    }

      
    // Set up the Boost logger with the retrieved log file path
    //setup_boost_logger(config.logFilePath);
    logger::construct_logger();
    LOG_TRACE   << "This is a trace message";
    LOG_DEBUG   << "This is a debug message";
    LOG_INFO    << "This is an info message";
    LOG_WARNING << "This is a warning message";
    LOG_ERROR   << "This is an error message";
    LOG_FATAL   << "This is a fatal message";
    
    // Set up Ethernet connection with retrieved IP and port
    setup_ethernet_connection(config.logReceiverIP, config.logReceiverPort);

    IPCMessageReceiver receiver(true , config.MessageQueue.c_str() );
    //std::cerr << "IPCMessageReceiver" << std::endl;
    
    
    while (true) {
        try {
            std::string received_message = receiver.receiveMessage();
            LOG_INFO << "Received message: " << received_message;
            
            // Log the message to the file
            if (std::filesystem::file_size(config.logFilePath) >= MAX_LOG_SIZE) {
                    rotate_log_file(config.logFilePath , config);
                }

            // Send the message over Ethernet
            send_log_to_ethernet(received_message);

        } catch (const IPCError &error) {
            LOG_ERROR << "Error: " << error.getErrorMessage();
            // Handle the error or exit as appropriate
        }
    }

    close(client_socket);

    return 0;
}
