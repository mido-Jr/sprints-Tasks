#ifndef PROJECT_IPC_LIBRARY_H
#define PROJECT_IPC_LIBRARY_H

#include <mqueue.h>
#include <iostream>
#include <syslog.h>
#include <errno.h> 
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <cstring>
#include <string>


std::string QUEUE_NAME = "/Sprints"; // Default log file path
#define QUEUE_PERMS ((int)(0666))
#define QUEUE_MAXMSG 10
#define QUEUE_MSGSIZE 1024

class IPCError {
public:
    IPCError(const std::string &message) : errorMessage(message) {}

    std::string getErrorMessage() const {
        return errorMessage;
    }

private:
    std::string errorMessage;
};

class IPCMessageReceiver {
public:
    IPCMessageReceiver(bool isBlocking, const std::string &QUEUE_NAME);
    ~IPCMessageReceiver();
    std::string receiveMessage();

private:
    mqd_t mqdes;
    struct mq_attr attr;
};

class IPCMessageSender {
public:
    IPCMessageSender(const std::string &QUEUE_NAME);
    ~IPCMessageSender();
    void sendMessage(const std::string &message);
    void logMessage(const std::string &message);

private:
    mqd_t mqdes;
};

#endif //PROJECT_IPC_LIBRARY_H
