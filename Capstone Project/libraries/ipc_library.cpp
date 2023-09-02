#include "ipc_library.h"


// IPCMessageReceiver constructor
IPCMessageReceiver::IPCMessageReceiver(bool isBlocking, const std::string &QUEUE_NAME) {
    attr.mq_maxmsg = QUEUE_MAXMSG;
    attr.mq_msgsize = QUEUE_MSGSIZE;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    mqdes = mq_open(QUEUE_NAME.c_str(), O_CREAT | O_RDWR  | (isBlocking ? 0 : O_NONBLOCK), QUEUE_PERMS, &attr);
    if (mqdes == -1) {
        throw IPCError("Failed to open or create message queue");
    }
}

// IPCMessageReceiver destructor
IPCMessageReceiver::~IPCMessageReceiver() {
    mq_close(mqdes);
    mq_unlink(QUEUE_NAME.c_str());
}

// IPCMessageReceiver receiveMessage method
std::string IPCMessageReceiver::receiveMessage() {
    char buf[QUEUE_MSGSIZE + 1];
    unsigned int prio = 0;

    ssize_t bytesRead = mq_receive(mqdes, buf, QUEUE_MSGSIZE, &prio);
    if (bytesRead == -1) {
        if (errno == EAGAIN) {
            throw IPCError("No messages available");
        } else {
            throw IPCError("Failed to receive message from queue");
        }
    }

    buf[bytesRead] = '\0';
    return std::string(buf);
}

// IPCMessageSender constructor
IPCMessageSender::IPCMessageSender(const std::string &QUEUE_NAME) {
    mqdes = mq_open(QUEUE_NAME.c_str(), O_WRONLY);
    if (mqdes == -1) {
        throw IPCError("Failed to open message queue for sender");
    }
}

// IPCMessageSender destructor
IPCMessageSender::~IPCMessageSender() {
    mq_close(mqdes);
}

// IPCMessageSender sendMessage method
void IPCMessageSender::sendMessage(const std::string &message) {
    if (mq_send(mqdes, message.c_str(), message.size(), 0) == -1) {
        throw IPCError("Failed to send message to queue");
    }
}

// IPCMessageSender logMessage method
void IPCMessageSender::logMessage(const std::string &message) {
    openlog("IPCMessageSender", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "%s", message.c_str());
    closelog();
}

