#ifndef PROJECT_FOLDER_LOGGER_H
#define PROJECT_FOLDER_LOGGER_H

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <string>

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    Logger();

    void initialize(const std::string& logFileName);
    void setLogLevel(LogLevel level);

    template <typename... Args>
    void log(LogLevel level, Args... args);

private:
    src::severity_logger_mt<LogLevel> logger;
    logging::formatter formatter;
};


#endif // PROJECT_FOLDER_LOGGER_H
